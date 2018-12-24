#pragma once

#include "entity/entity.h"

class SnakeJoint : public Entity
{
public:
    enum TypeJoint {head, joint, tail} typeJoint;
    enum Direction {left, right, top, down} dir;
public:
    SnakeJoint(TypeJoint typeJoint = TypeJoint::joint, Direction dir = Direction::right);
};
