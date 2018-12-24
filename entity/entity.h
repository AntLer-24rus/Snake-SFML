#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
public:
    sf::String name;
    float x;
    float y;

public:
    Entity(sf::String name, float x = 0, float y = 0);
    void setColor(sf::Color color) {_shape.setFillColor(color);}
    void setName(sf::String name) {this->name = name;}

private:
    sf::CircleShape _shape;

    // Drawable interface
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
