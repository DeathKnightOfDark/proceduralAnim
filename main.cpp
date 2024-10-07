#include <SFML/Graphics.hpp>
#include "bone.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape rShap(sf::Vector2f{200.0f, 50.0f});
    rShap.setFillColor(sf::Color::Red);
    rShap.setPosition(sf::Vector2f{400.0f, 400.0f});
    bone k{ sf::Vector2f{400.0f,425.f},sf::Vector2f{600.0f,425.0f} };
    k.link_linkedTransformable(&rShap);
    k.updateJoints();
    sf::Clock t;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (t.getElapsedTime().asMilliseconds() > 100)
        {
            k.rotateBone(360 * t.getElapsedTime().asSeconds());
            t.restart();
        }

        window.clear();
        //window.draw(shape);
        k.drawBone(window);
        window.draw(rShap);
        window.display();
    }

    return 0;
}