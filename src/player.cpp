#include "player.h"

Player::Player()
{
    posX = leftMargin;
    posY = topMargin;
    face = Face::LEFT;
    setPix();
}

int Player::Col()
{
    return (this->posX - leftMargin) / length;
}

int Player::Row()
{
    return (this->posY - topMargin) / length;
}

void Player::move(int _dRow, int _dCol)
{
    this->step++;
    this->posX += length * _dCol;
    this->posY += length * _dRow;
    if(_dRow == 1 && _dCol == 0)
    {
        face = Face::DOWN;
    }
    else if(_dRow == -1 && _dCol == 0)
    {
        face = Face::UP;
    }
    else if(_dRow == 0 && _dCol == 1)
    {
        face = Face::RIGHT;
    }
    else if(_dRow == 0 && _dCol == -1)
    {
        face = Face::LEFT;
    }
    this->setPix(); //更新贴图
}

void Player::reset(int _Row, int _Col)
{
    posX = length * _Col + leftMargin;
    posY = length * _Row + topMargin;;
    step = 0;
    face = Face::LEFT;
    setPix();
}

void Player::setPix()
{
    switch(this->face)
    {
    case Face::DOWN:
        pix.load(":/res/Player_down.png");
        break;
    case Face::UP:
        pix.load(":/res/Player_up.png");
        break;
    case Face::LEFT:
        pix.load(":/res/Player_left.png");
        break;
    case Face::RIGHT:
        pix.load(":/res/Player_right.png");
        break;
    }
}
