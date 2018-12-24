#include "entity.h"

Entity::Entity(sf::String name, float x, float y)
{
    this->name = name;
    this->_shape = sf::CircleShape(48.f/2);
    this->_shape.setFillColor(sf::Color(0x00, 0xFF, 0x00));
    this->_shape.setOrigin(48.f/2, 48.f/2);
    this->x = x;
    this->y = y;
    move(x, y);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_shape, states);

    sf::RectangleShape ox({48, 2});
    ox.setPosition(-24,24);
    ox.setFillColor(sf::Color::Red);
    sf::RectangleShape oy({2, 48});
    oy.setPosition(-24,-24);
    oy.setFillColor(sf::Color::Green);
    //ox.setOrigin(48.f/2, 48.f/2);

    sf::ConvexShape arrowTriangle;
    arrowTriangle.setPointCount(3);
    arrowTriangle.setPoint(0, {42, 24});
    arrowTriangle.setPoint(1, {30, 36});
    arrowTriangle.setPoint(2, {30, 12});
    arrowTriangle.setFillColor(sf::Color::Red);
    arrowTriangle.setOrigin(48.f/2, 48.f/2);

    sf::RectangleShape arrowRectangle({30,10});
    arrowRectangle.setPosition(6, 19);
    arrowRectangle.setFillColor(sf::Color::Red);
    arrowRectangle.setOrigin(48.f/2, 48.f/2);

    sf::Font font;
    font.loadFromFile("CyrilicOld.TTF");
    sf::Text text(this->name,font, 15);
    text.setFillColor(sf::Color::Blue);
    text.setOrigin(48.f/2 - 10, 48.f/2 - 4);

//    target.draw(ox, states);
//    target.draw(oy, states);
    target.draw(arrowTriangle, states);
    target.draw(arrowRectangle, states);
    target.draw(text, states);
}
