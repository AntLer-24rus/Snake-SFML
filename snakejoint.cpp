#include "snakejoint.h"

SnakeJoint::SnakeJoint(sf::String name, TypeJoint typeJoint, Direction dir) : Entity (name)
{
    this->typeJoint = typeJoint;
    this->dir = dir;
}

void SnakeJoint::update()
{
    this->dir = _prev->dir;
}
