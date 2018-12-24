#pragma once

#include "entity/entity.h"
#include <SFML/System.hpp>

class SnakeJoint : public Entity
{
public:
    enum TypeJoint {head, joint, tail} typeJoint;
    enum Direction {left, right, top, down} dir;
public:
    SnakeJoint(sf::String name = "SnakeJoint", TypeJoint typeJoint = TypeJoint::joint, Direction dir = Direction::right);
    void update();

    SnakeJoint* getNextJount(){return this->_next;}
    void setNextJoint(SnakeJoint *next){this->_next = next;}

    SnakeJoint* getPrevJount(){return this->_prev;}
    void setPrevJoint(SnakeJoint *prev){this->_prev = prev;}
private:
    SnakeJoint *_next = nullptr;
    SnakeJoint *_prev = nullptr;
};
