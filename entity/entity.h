#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
public:
    Entity();

private:
    sf::RectangleShape shape;

    // Drawable interface
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
