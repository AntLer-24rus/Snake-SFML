#include "snake.h"
#include <iostream>
#include <math.h>

Snake::Snake(float x, float y)
{
    SnakeJoint *head = new SnakeJoint(SnakeJoint::TypeJoint::head);
    SnakeJoint *joint = new SnakeJoint(SnakeJoint::TypeJoint::joint);
    SnakeJoint *tail = new SnakeJoint(SnakeJoint::TypeJoint::tail, SnakeJoint::Direction::top);

    head->setName("H");
    joint->setName("J1");
    tail->setName("T");

    this->body.push_back(head);
    this->body.push_back(joint);
    this->body.push_back(tail);

    this->x = x;
    this->y = y;
}

void Snake::addJoint(SnakeJoint *joint)
{
    this->body.insert(--this->body.end(), joint);
}

void Snake::update(float time)
{
    bool updateDir = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) & (this->body[0]->dir == SnakeJoint::Direction::top |
                                                           this->body[0]->dir == SnakeJoint::Direction::down)) {
        this->body[0]->dir = SnakeJoint::Direction::right;
        updateDir = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & (this->body[0]->dir == SnakeJoint::Direction::top |
                                                          this->body[0]->dir == SnakeJoint::Direction::down)) {
        this->body[0]->dir = SnakeJoint::Direction::left;
        updateDir = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) & (this->body[0]->dir == SnakeJoint::Direction::left |
                                                        this->body[0]->dir == SnakeJoint::Direction::right)) {
        this->body[0]->dir = SnakeJoint::Direction::top;
        updateDir = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) & (this->body[0]->dir == SnakeJoint::Direction::left |
                                                        this->body[0]->dir == SnakeJoint::Direction::right)) {
        this->body[0]->dir = SnakeJoint::Direction::down;
        updateDir = true;
    }

    int dirX = 0;
    int dirY = 0;

    switch (this->body[0]->dir) {
    case SnakeJoint::Direction::right:
    {
        dirX = 1;
        break;
    }
    case SnakeJoint::Direction::left:
    {
        dirX = -1;
        break;
    }
    case SnakeJoint::Direction::top:
    {
        dirY = -1;
        break;
    }
    case SnakeJoint::Direction::down:
    {
        dirY = 1;
        break;
    }
    }
    this->x += 48 * dirX * time;
    this->y += 48 * dirY * time;

    std::cout << time << std::endl;

    if (fmodf(this->x, 48.f) > 44 | fmodf(this->y, 48.f) > 44) {
        for (auto i = this->body.size() - 1; i > 0; i--) {
            SnakeJoint::Direction nextDir = this->body[i-1]->dir;

            //std::string tmp = this->body[i]->name;
            //std::cout << "dir " << i << " " << tmp << " " << this->body[i]->dir << "->" << nextDir << std::endl;
            this->body[i]->dir = nextDir;
            //curSnakeJoint->dir = prevSnakeJoint->dir;

        }
    }
}


void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    float angle;
    float xOffset = 0;
    float yOffset = 0;
    switch (this->body[0]->dir) {
    case SnakeJoint::Direction::right:
    {
        xOffset = 48.f;
        angle = 0;
        break;
    }
    case SnakeJoint::Direction::left:
    {
        xOffset = -48.f;
        angle = 180;
        break;
    }
    case SnakeJoint::Direction::top:
    {
        xOffset = 0;
        yOffset = -48.f;

        angle = 90;
        break;
    }
    case SnakeJoint::Direction::down:
    {
        xOffset = 0;
        yOffset = 48.f;
        angle = -90;
        break;
    }

    }

    //this->body[0]->setRotation(angle);
    states.transform.translate({this->x + xOffset, this->y + yOffset});
    states.transform.rotate(angle);



    for (unsigned int i = 0; i < this->body.size(); ++i) {
        SnakeJoint *curSnakeJoint = this->body[i];
        sf::Transform mv = sf::Transform();
        std::string direct = "";


        switch (curSnakeJoint->dir) {
        case SnakeJoint::Direction::right:
        {
            direct = "right";
            if(angle != 0) {
                mv.rotate(-angle);
                angle += -angle;
            }
            break;
        }
        case SnakeJoint::Direction::left:
        {
            direct = "left";
            if (angle != 180) {
                mv.rotate(180 - angle);
                angle += 180 - angle;
            }
            break;
        }
        case SnakeJoint::Direction::top:
        {
            direct = "top";
            if (angle > -90) {
                mv.rotate(-90 - angle);
                angle += -90 - angle;
            }
            break;
        }
        case SnakeJoint::Direction::down:
        {
            direct = "down";
            if (angle != 90) {
                mv.rotate(90 - angle);
                angle += 90 - angle;
            }
            break;
        }
        }

        std::string tmp = curSnakeJoint->name;
        //std::cout << "angle " << direct << " for joint[\"" << tmp << "\"] = " << angle << std::endl;
        mv.translate(-48.f, 0);

        switch (curSnakeJoint->typeJoint) {
        case SnakeJoint::TypeJoint::head:
        {
            //mv.translate(this->x, this->y);
            curSnakeJoint->setColor(sf::Color::Cyan);
            break;
        }
        case SnakeJoint::TypeJoint::joint:
        {
            curSnakeJoint->setColor(sf::Color::Yellow);
            break;
        }
        case SnakeJoint::TypeJoint::tail:
        {
            curSnakeJoint->setColor(sf::Color::Magenta);
            break;
        }
        }

        states.transform *= mv;
        target.draw(*curSnakeJoint, states);
    }
}
