#include "entity.h"

Entity::Entity()
{
  shape = sf::RectangleShape(sf::Vector2f(50.f, 100.f));
  shape.setFillColor(sf::Color(0x00, 0x00, 0xFF));
  shape.setPosition(100, 100);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(shape, states);
}
