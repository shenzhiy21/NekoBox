#ifndef CELL_H
#define CELL_H
#include "define.h"
#include <QColor>
#include <QPixmap>

enum CellType
{
    WALL,
    TARGET,     //目标点位
    BOX,
    INTARGET,   //箱子进入目标点位
    EMPTY       //啥也没有
};

class Cell
{
public:
    int posX;
    int posY;
    int width = length;
    int height = length;
    int cellType;
    QPixmap pix;
public:
    Cell(int x = 0, int y = 0, int celltype = CellType::EMPTY);
    void setPix(int _cellType);       //设置图片
    void update();      //更新地图状态
    int Row();
    int Col();
};

#endif // CELL_H
