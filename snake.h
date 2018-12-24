#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include "entity/entity.h"
#include "snakejoint.h"

class Snake : public sf::Drawable
{
public:
    std::vector<SnakeJoint*> body;
    float x;
    float y;
    Snake(float x, float y);

    void addJoint(SnakeJoint *joint);
    void update(float time);
    // Drawable interface
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // SNAKE_H
