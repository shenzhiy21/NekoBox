#ifndef PLAYER_H
#define PLAYER_H

#include "define.h"
#include <QPixmap>

enum Face
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Player
{
public:
    int posX;
    int posY;
    int width = length;
    int height = length;
    int face = Face::LEFT;        //朝向
    QPixmap pix;                  //贴图
    int step = 0;                 //总的操作次数
public:
    Player();
    int Row();       //获取玩家当前的行和列信息
    int Col();
    void move(int _dRow, int _dCol);
    void reset(int _Row, int _Col);     //重置玩家位置
    void update();  //TODO：人物移动后更新贴图，需要加到每次移动的游戏逻辑后面
    void setPix();
};

#endif // PLAYER_H
