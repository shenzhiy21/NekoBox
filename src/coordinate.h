#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
public:
    Coordinate(int _row = 0, int _col = 0) : row(_row), col(_col) {}
    Coordinate(const Coordinate &other);
    int row;
    int col;
    int distance(Coordinate other); //曼哈顿距离，亦即最少需要多少步才能走到下一个格子
};

#endif // COORDINATE_H
