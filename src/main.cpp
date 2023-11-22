#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(858, 525), "Pong Remake", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed &&
                event.key.scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        }
    
        window.clear();

        window.display();
    }

    return 0;
}