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
    void update(sf::Keyboard::Key releasedKey);
private:
    SnakeJoint *_head;
    SnakeJoint *_tail;
protected:
    // Drawable interface
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // SNAKE_H
