#include <SFML/Graphics.hpp>

#include "entity/entity.h"
#include "snake.h"

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape shape(sf::Vector2f(48.f, 48.f));
    shape.setPosition(24 + 48 * 6, 24 +  48 * 6);
    shape.setOrigin(48.f/2, 48.f/2);

    Snake snake = Snake(24 + 48 * 6, 24 +  48 * 6);

    SnakeJoint *joint2 = new SnakeJoint();
    joint2->setName("J2");
    joint2->dir = SnakeJoint::Direction::top;
    snake.addJoint(joint2);

    SnakeJoint *joint3 = new SnakeJoint("J3");
    //joint3->dir = SnakeJoint::Direction::left;
    snake.addJoint(joint3);

    SnakeJoint *joint4 = new SnakeJoint();
    joint4->setName("J4");
    joint4->dir = SnakeJoint::Direction::down;
    snake.addJoint(joint4);

    SnakeJoint *joint5 = new SnakeJoint();
    joint5->setName("J5");
    //joint5->dir = SnakeJoint::Direction::left;
    snake.addJoint(joint5);

    std::cout << "Snake size " << snake.body.size() << std::endl;




    float dx;
    float dy;
    dx = 48;
    dy = 0;
    sf::Clock clock;
    sf::Keyboard::Key releasedKey = sf::Keyboard::Unknown;



    while (window.isOpen())
    {

//        dx = 0;
//        dy = 0;
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {

            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::KeyReleased:
            {
                releasedKey = event.key.code;
                switch (event.key.code) {
                case sf::Keyboard::Up:
                {
                    dx = 0;
                    dy = -48;
                    break;
                }
                case sf::Keyboard::Down:
                {
                    dx = 0;
                    dy = 48;
                    break;
                }
                case sf::Keyboard::Left:
                {
                    dx = -48;
                    dy = 0;
                    break;
                }
                case sf::Keyboard::Right:
                {
                    dx = 48;
                    dy = 0;
                    break;
                }
                }
                break;
            }
            }

        }

        float time = clock.getElapsedTime().asMicroseconds();
        if (time >= 200000) {
            clock.restart();
            snake.update(releasedKey);
            releasedKey = sf::Keyboard::Unknown;
        }

        //time /= 300000;


        window.clear();

        window.draw(snake);

        window.display();


    }

    return 0;
}
