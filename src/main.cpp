#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <iostream>

struct Ball : sf::CircleShape {
    explicit Ball(float radius = 0) {
        this->setRadius(radius);
    }
    float ballSpeedX = 150.f, ballSpeedY = 150.f;
};

struct Paddle : sf::RectangleShape {
    explicit Paddle(const sf::Vector2f& size = sf::Vector2f(0, 0), const sf::Vector2f& pos = sf::Vector2f(0, 0)) {
        this->setSize(size);
        this->setPosition(pos);
    };
    float paddleSpeed = 400.f;
    int score = 0;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Remake", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Font font;
    if (!font.loadFromFile("assets/bit5x3.ttf"));
    sf::Clock deltaClock;
    float deltaTime;
    sf::Vertex lines[40];

    for (int i=0; i < std::size(lines); i++) {
        lines[i].position = { window.getSize().x / 2.f, lines[i - 1].position.y + 15.f};
    }

    Paddle paddleRight({ 10.f, 100.f }, { 50.f - paddleRight.getSize().x / 2.f, window.getSize().y / 2.f - paddleRight.getSize().y / 2.f});
    sf::Text textRight(std::to_string(paddleRight.score), font, 90);
    textRight.setPosition({ window.getSize().x - window.getSize().x / 4.f - 45.f, 50.f});

    Paddle paddleLeft({ 10.f, 100.f }, { window.getSize().x - 50.f + paddleLeft.getSize().x / 2.f, window.getSize().y / 2.f - paddleLeft.getSize().y / 2.f});
    sf::Text textLeft(std::to_string(paddleLeft.score), font, 90);
    textLeft.setPosition({ window.getSize().x / 4.f - 45.f, 50.f});

    Ball ball(5.f);
    ball.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f});

    sf::Text winnerText("", font, 60);
    winnerText.setFillColor(sf::Color::Yellow);
    sf::Text replayText("", font, 30);
    replayText.setFillColor(sf::Color::Yellow);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed &&
                event.key.scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        }

        deltaTime = deltaClock.restart().asSeconds();

        if (paddleRight.getPosition().y < 25.f)
            paddleRight.setPosition({ paddleRight.getPosition().x, 25.f });
        else if (paddleRight.getPosition().y + paddleRight.getSize().y > window.getSize().y - 25.f)
            paddleRight.setPosition({ paddleRight.getPosition().x, window.getSize().y - paddleRight.getSize().y - 25.f});

        if (paddleLeft.getPosition().y < 25.f)
            paddleLeft.setPosition({ paddleLeft.getPosition().x, 25.f });
        else if (paddleLeft.getPosition().y + paddleLeft.getSize().y > window.getSize().y - 25.f)
            paddleLeft.setPosition({ paddleLeft.getPosition().x, window.getSize().y - paddleLeft.getSize().y - 25.f});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
            paddleRight.move(sf::Vector2f(0.f, -1.f) * paddleRight.paddleSpeed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
            paddleRight.move(sf::Vector2f(0.f, 1.f) * paddleRight.paddleSpeed * deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
            paddleLeft.move(sf::Vector2f(0.f, -1.f) * paddleLeft.paddleSpeed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
            paddleLeft.move(sf::Vector2f(0.f, 1.f) * paddleLeft.paddleSpeed * deltaTime);

        if (ball.getGlobalBounds().intersects(paddleRight.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(paddleLeft.getGlobalBounds()))
            ball.ballSpeedX *= -1.1f;
        
        if (ball.getPosition().y < 0.f)
            ball.ballSpeedY *= -1.1f;
        if (ball.getPosition().y >= window.getSize().y)
            ball.ballSpeedY *= -1.1f;

        if (ball.getPosition().x < 0.f) {
            paddleRight.score += 1;
            textRight.setString(std::to_string(paddleRight.score));
            winnerText.setString("Player Right Wins!");
            ball.setPosition({ 0.f, -10.f});
            ball.ballSpeedX = ball.ballSpeedY = 0.f;
        }
        if (ball.getPosition().x > window.getSize().x) {
            paddleLeft.score += 1;
            textLeft.setString(std::to_string(paddleLeft.score));
            winnerText.setString("Player Left Wins!");
            ball.setPosition({ 0.f, -10.f});
            ball.ballSpeedX = ball.ballSpeedY = 0.f;
        }
        if (winnerText.getString().getSize() > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            winnerText.setString("");
            ball.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f});
            ball.ballSpeedX = ball.ballSpeedY = 200.f;
        }
        
        ball.move(sf::Vector2f(1.f * ball.ballSpeedX, 1.f * ball.ballSpeedY) * deltaTime);
    
        window.clear();

        window.draw(lines, std::size(lines), sf::Lines);
        window.draw(ball);
        window.draw(paddleRight);
        window.draw(paddleLeft);
        window.draw(textRight);
        window.draw(textLeft);

        if (winnerText.getString().getSize() > 0) {
            replayText.setString("Press SPACE to replay");
            winnerText.setPosition({ window.getSize().x / 2.f - winnerText.getGlobalBounds().width / 2.f, window.getSize().y / 2.f - 60.f});
            replayText.setPosition({ window.getSize().x / 2.f - replayText.getGlobalBounds().width / 2.f, window.getSize().y / 2.f});
            window.draw(winnerText);
            window.draw(replayText);
        }

        window.display();
    }

    return 0;
}