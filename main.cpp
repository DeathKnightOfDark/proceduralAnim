#include <SFML/Graphics.hpp>
#include "bone.h"
#include <iostream>
int main()
{
  
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "procedural animation");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape rShap(sf::Vector2f{200.0f, 50.0f});
    rShap.setFillColor(sf::Color::Red);
    rShap.setPosition(sf::Vector2f{400.0f, 400.0f});
    bone k{ sf::Vector2f{400.0f,424.f},200.0f, 0 };
    
    //k.link_linkedTransformable(&rShap);
    //k.updateJoints();
    k.addAncestor(bone{ k.get_boneOtherJointPos_glob(), 100.0f, 90.0f });
    sf::Clock t;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (t.getElapsedTime().asMilliseconds() > 16)
        {
            k.rotateBone(120 * t.getElapsedTime().asSeconds());
            //k.rotateBone(0);
            k.moveBone(sf::Vector2f{50.0f, 50.0f} * t.getElapsedTime().asSeconds());
            t.restart();
        }

        window.clear();
        //window.draw(shape);
        //window.draw(rShap);
        k.drawBone(window);
        
        window.display();
    }

    return 0;
}