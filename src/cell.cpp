#include "cell.h"

Cell::Cell(int x, int y, int celltype)
{
    posX = x;
    posY = y;
    cellType = celltype;
    setPix(celltype);
}

void Cell::setPix(int celltype)
{
    switch(celltype)
    {
    case CellType::BOX:
        pix.load(":/res/Box.png");
        break;
    case CellType::WALL:
        pix.load(":/res/Wall.png");
        break;
    case CellType::EMPTY:
        pix.load(":/res/Empty.png");
        break;
    case CellType::TARGET:
        pix.load(":/res/Target.png");
        break;
    case CellType::INTARGET:
        pix.load(":/res/Intarget.png");
        break;
    }
}

void Cell::update()
{
    setPix(cellType);
}

int Cell::Row()
{
    return (this->posY - topMargin) / length;
}

int Cell::Col()
{
    return (this->posX - leftMargin) / length;
}
