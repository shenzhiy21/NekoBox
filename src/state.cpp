#include "state.h"

State::State()
{
    pos = Coordinate(0, 0);
    isPush = false;
    face = Face::DOWN;
}

State::State(int _row, int _col, bool _isPush, int _face)
{
    Coordinate c(_row, _col);
    pos = c;
    isPush = _isPush;
    face = _face;
}

State::State(Player _player, bool _isPush)
{
    Coordinate c(_player.Row(), _player.Col());
    pos = c;
    isPush = _isPush;
    face = _player.face;
}

