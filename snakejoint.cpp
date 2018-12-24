#include "snakejoint.h"

SnakeJoint::SnakeJoint(TypeJoint typeJoint, Direction dir) : Entity ("SnakeJoint")
{
    this->typeJoint = typeJoint;
    this->dir = dir;
}
