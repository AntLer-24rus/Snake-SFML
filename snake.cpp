#include "snake.h"
#include <iostream>
#include <math.h>

Snake::Snake(float x, float y)
{
    this->_head = new SnakeJoint("H", SnakeJoint::TypeJoint::head, SnakeJoint::Direction::down);
    this->_tail = new SnakeJoint("T", SnakeJoint::TypeJoint::tail, SnakeJoint::Direction::top);
    this->addJoint(_tail);
    this->addJoint(new SnakeJoint("J1", SnakeJoint::TypeJoint::joint));
//    this->body.push_back(new SnakeJoint("H", SnakeJoint::TypeJoint::head));
//    this->body.push_back(new SnakeJoint("J1", SnakeJoint::TypeJoint::joint));
//    this->body.push_back(new SnakeJoint("T", SnakeJoint::TypeJoint::tail, SnakeJoint::Direction::top));

    this->x = x;
    this->y = y;
}

void Snake::addJoint(SnakeJoint *joint)
{
    SnakeJoint *tmp = this->_head->getNextJount();

    if (tmp != nullptr) {
        tmp->setPrevJoint(joint);
    }


    joint->setPrevJoint(this->_head);
    joint->setNextJoint(tmp);

    this->_head->setNextJoint(joint);
    //this->body.insert(--this->body.end(), joint);
}

void Snake::update(sf::Keyboard::Key releasedKey)
{


    if ((releasedKey == sf::Keyboard::Right) & (this->_head->dir == SnakeJoint::Direction::top |
                                                           this->_head->dir == SnakeJoint::Direction::down)) {
        this->_head->dir = SnakeJoint::Direction::right;

    }
    if ((releasedKey == sf::Keyboard::Left) & (this->_head->dir == SnakeJoint::Direction::top |
                                                          this->_head->dir == SnakeJoint::Direction::down)) {
        this->_head->dir = SnakeJoint::Direction::left;

    }
    if ((releasedKey == sf::Keyboard::Up) & (this->_head->dir == SnakeJoint::Direction::left |
                                                        this->_head->dir == SnakeJoint::Direction::right)) {
        this->_head->dir = SnakeJoint::Direction::top;

    }
    if ((releasedKey == sf::Keyboard::Down) & (this->_head->dir == SnakeJoint::Direction::left |
                                                        this->_head->dir == SnakeJoint::Direction::right)) {
        this->_head->dir = SnakeJoint::Direction::down;

    }

    int dirX = 0;
    int dirY = 0;

    switch (this->_head->dir) {
    case SnakeJoint::Direction::right:
    {
        dirX = 1;
        dirY = 0;
        break;
    }
    case SnakeJoint::Direction::left:
    {
        dirX = -1;
        dirY = 0;
        break;
    }
    case SnakeJoint::Direction::top:
    {
        dirX = 0;
        dirY = -1;
        break;
    }
    case SnakeJoint::Direction::down:
    {
        dirX = 0;
        dirY = 1;
        break;
    }
    }


    float dx = 48 * dirX;
    float dy = 48 * dirY;


    std::cout << ceilf(this->x / 48.f) - ceilf((this->x + releasedKey) / 48.f) << std::endl;

    //if (ceilf(this->x / 48.f) - ceilf((this->x + releasedKey) / 48.f) < 0 | ceilf(this->y / 48.f) - ceilf((this->y + dy) / 48.f) < 0) {

        SnakeJoint *curSnakeJoint = this->_tail;
        while(curSnakeJoint != this->_head){
            curSnakeJoint->update();
            curSnakeJoint = curSnakeJoint->getPrevJount();
        }

//        for (auto i = this->body.size() - 1; i > 0; i--) {
//            SnakeJoint::Direction nextDir = this->body[i-1]->dir;

//            //std::string tmp = this->body[i]->name;
//            //std::cout << "dir " << i << " " << tmp << " " << this->body[i]->dir << "->" << nextDir << std::endl;
//            this->body[i]->dir = nextDir;
//            //curSnakeJoint->dir = prevSnakeJoint->dir;

//        }
    //}

    this->x += dx;
    this->y += dy;
}


void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    float angle;
    float xOffset = 0;
    float yOffset = 0;
    //switch (this->body[0]->dir) {
    switch (this->_head->dir) {
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


     SnakeJoint *curSnakeJoint = this->_head;
    //for (unsigned int i = 0; i < this->body.size(); ++i) {
     while(curSnakeJoint != nullptr){
        //SnakeJoint *curSnakeJoint = this->body[i];
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

            if (angle != 180) {
                direct = "left";
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
        curSnakeJoint = curSnakeJoint->getNextJount();
    }
}
