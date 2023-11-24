#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Remake", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;

    float ballSpeedX = .35f;
    float ballSpeedY = .35f;
    float paddleSpeed = 1.f;

    sf::RectangleShape paddleRight({ 10.f, 100.f });
    paddleRight.setPosition({ 50.f - paddleRight.getSize().x / 2.f, window.getSize().y / 2.f - paddleRight.getSize().y / 2.f});

    sf::RectangleShape paddleLeft({ 10.f, 100.f });
    paddleLeft.setPosition({ window.getSize().x - 50.f + paddleLeft.getSize().x / 2.f, window.getSize().y / 2.f - paddleLeft.getSize().y / 2.f});

    sf::CircleShape ball(5.f);
    ball.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f});

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed &&
                event.key.scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        }

        if (paddleRight.getPosition().y <= 25.f)
            paddleRight.setPosition({ paddleRight.getPosition().x, 25.f });
        if (paddleRight.getPosition().y + paddleRight.getSize().y >= window.getSize().y - 25.f)
            paddleRight.setPosition({ paddleRight.getPosition().x, window.getSize().y - paddleRight.getSize().y - 25.f});

        if (paddleLeft.getPosition().y < 25.f)
            paddleLeft.setPosition({ paddleLeft.getPosition().x, 25.f });
        if (paddleLeft.getPosition().y + paddleLeft.getSize().y >= window.getSize().y - 25.f)
            paddleLeft.setPosition({ paddleLeft.getPosition().x, window.getSize().y - paddleLeft.getSize().y - 25.f});

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
            ballSpeedX *= -1.f;
        
        if (ball.getPosition().y < 0.f)
            ballSpeedY *= -1.f;
        if (ball.getPosition().y + ball.getRadius() >= window.getSize().y)
            ballSpeedY *= -1.f;
        
        ball.move(sf::Vector2f(1.f * ballSpeedX, 1.f * ballSpeedY));
    
        window.clear();

        window.draw(ball);
        window.draw(paddleRight);
        window.draw(paddleLeft);

        window.display();
    }

    return 0;
}