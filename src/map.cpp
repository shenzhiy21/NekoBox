#include "map.h"
#include <fstream>
#include <iostream>

Map::Map()
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            Arr[i][j] = Cell(j * length + leftMargin, i * length + topMargin);
        }
    }
}

void Map::InitByFile(std::string filename)
{
    std::ifstream fin(filename);
    for(int y = 0; y < ROW; y++)
    {
        std::string str;
        fin >> str;
        assert(fin);
        assert(str.size() >= COLUMN);
        for(int x = 0; x < COLUMN; x++)
        {
            Arr[y][x].cellType = str[x] - '0';
            Arr[y][x].update();
        }
    }
    fin.close();
}

//检查是否成功
bool Map::Success()
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            //如果发现某个地方仍然是目标点，就说明没有成功
            if(Arr[i][j].cellType == CellType::TARGET) return false;
        }
    }
    return true;
}
