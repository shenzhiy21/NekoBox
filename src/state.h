//用于实现回退功能的状态类。
//需要存放位置信息、是否推了箱子、以及玩家的朝向
//玩家的朝向其实可以由前后两个位置信息推断出来，但方便起见还是维护一下，问就是我太懒了

#ifndef STATE_H
#define STATE_H

#include <coordinate.h>
#include <player.h>

class State
{
public:
    State();
    State(int _row, int _col, bool _isPush, int _face);
    State(Player _player, bool _isPush);
    Coordinate pos;
    bool isPush;    //是否推了箱子
    int face;
};

#endif // STATE_H
