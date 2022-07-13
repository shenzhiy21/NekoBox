#ifndef MAP_H
#define MAP_H
#include "cell.h"
#include "define.h"
#include <string>

class Map
{
public:
    Map();
    void InitByFile(std::string filename);
    bool Success();

    Cell Arr[ROW][COLUMN];
};

#endif // MAP_H
