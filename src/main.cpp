#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Remake", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Font font;
    if (!font.loadFromFile("src/bit5x3.ttf"));
    sf::Vertex line[2];

    line[0].position = { window.getSize().x / 2.f, 0.f};
    line[1].position = { window.getSize().x / 2.f, (float) window.getSize().y};

    float ballSpeedX = 2.5f;
    float ballSpeedY = 2.5f;
    float paddleSpeed = 5.f;

    int scoreRight = 0;
    sf::Text textRight(std::to_string(scoreRight), font, 90);
    textRight.setPosition({ window.getSize().x - window.getSize().x / 4.f - 45.f, 50.f});
    sf::RectangleShape paddleRight({ 10.f, 100.f });
    paddleRight.setPosition({ 50.f - paddleRight.getSize().x / 2.f, window.getSize().y / 2.f - paddleRight.getSize().y / 2.f});

    int scoreLeft = 0;
    sf::Text textLeft(std::to_string(scoreLeft), font, 90);
    textLeft.setPosition({ window.getSize().x / 4.f - 45.f, 50.f});
    sf::RectangleShape paddleLeft({ 10.f, 100.f });
    paddleLeft.setPosition({ window.getSize().x - 50.f + paddleLeft.getSize().x / 2.f, window.getSize().y / 2.f - paddleLeft.getSize().y / 2.f});

    sf::CircleShape ball(5.f);
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

        if (paddleRight.getPosition().y < 25.f) {
            paddleRight.setPosition({ paddleRight.getPosition().x, 25.f });
            paddleSpeed = 5.f;
        }
        else if (paddleRight.getPosition().y + paddleRight.getSize().y > window.getSize().y - 25.f) {
            paddleRight.setPosition({ paddleRight.getPosition().x, window.getSize().y - paddleRight.getSize().y - 25.f});
            paddleSpeed = 5.f;
        } else paddleSpeed = 5.f;

        if (paddleLeft.getPosition().y < 25.f) {
            paddleLeft.setPosition({ paddleLeft.getPosition().x, 25.f });
            paddleSpeed = 5.f;
        }
        else if (paddleLeft.getPosition().y + paddleLeft.getSize().y > window.getSize().y - 25.f) {
            paddleLeft.setPosition({ paddleLeft.getPosition().x, window.getSize().y - paddleLeft.getSize().y - 25.f});
            paddleSpeed = 5.f;
        } else paddleSpeed = 5.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
            paddleRight.move(sf::Vector2f(0.f, -1.f) * paddleSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
            paddleRight.move(sf::Vector2f(0.f, 1.f) * paddleSpeed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
            paddleLeft.move(sf::Vector2f(0.f, -1.f) * paddleSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
            paddleLeft.move(sf::Vector2f(0.f, 1.f) * paddleSpeed);

        if (ball.getGlobalBounds().intersects(paddleRight.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(paddleLeft.getGlobalBounds()))
            ballSpeedX *= -1.1f;
        
        if (ball.getPosition().y < 0.f)
            ballSpeedY *= -1.1f;
        if (ball.getPosition().y + ball.getRadius() >= window.getSize().y)
            ballSpeedY *= -1.1f;

        if (ball.getPosition().x < 0.f) {
            scoreRight += 1;
            textRight.setString(std::to_string(scoreRight));
            winnerText.setString("Player Right Wins!");
            ball.setPosition({ 0.f, -5.f});
            ballSpeedX = ballSpeedY = 0.f;
        }
        if (ball.getPosition().x > window.getSize().x) {
            scoreLeft += 1;
            textLeft.setString(std::to_string(scoreLeft));
            winnerText.setString("Player Left Wins!");
            ball.setPosition({ 0.f, -5.f});
            ballSpeedX = ballSpeedY = 0.f;
        }
        if (winnerText.getString().getSize() > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            winnerText.setString("");
            ball.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f});
            ballSpeedX = ballSpeedY = 2.5f;
        }
        
        ball.move(sf::Vector2f(1.f * ballSpeedX, 1.f * ballSpeedY));
    
        window.clear();

        window.draw(line, 2, sf::Lines);
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