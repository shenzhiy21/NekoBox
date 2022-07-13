//该文件负责实现mainwindow类里的游戏逻辑：人物移动、推箱子、游戏重置、回退

#include <mainwindow.h>

void MainWindow::collision(int _dRow, int _dCol)
{
    bool isMove = false;    //是否移动了
    bool isPush = false;    //是否推箱子了

    //记录玩家当前所在位置以及朝向
    int nowRow = player.Row();
    int nowCol = player.Col();
    int nowFace = player.face;

    //玩家下一时刻即将到达的位置
    int newRow = nowRow + _dRow;
    int newCol = nowCol + _dCol;
    auto& cell = map.Arr[newRow][newCol];
    assert(newRow + _dRow >= 0 && newRow + _dRow < ROW);
    assert(newCol + _dCol >= 0 && newCol + _dCol < COLUMN);
    auto& next_cell = map.Arr[newRow + _dRow][newCol + _dCol];

    if(cell.cellType == CellType::WALL) return;
    else if(cell.cellType == CellType::BOX)
    {
        //如果箱子前面没有障碍物
        if(next_cell.cellType == CellType::EMPTY)
        {
            cell.cellType = CellType::EMPTY;
            next_cell.cellType = CellType::BOX;
            player.move(_dRow, _dCol);
            isMove = true;
            isPush = true;
        }
        //如果箱子前面就是目标点
        else if(next_cell.cellType == CellType::TARGET)
        {
            cell.cellType = CellType::EMPTY;
            next_cell.cellType = CellType::INTARGET;
            player.move(_dRow, _dCol);
            isMove = true;
            isPush = true;
        }
    }
    else if(cell.cellType == CellType::INTARGET)
    {
        if(next_cell.cellType == CellType::EMPTY)
        {
            cell.cellType = CellType::TARGET;
            next_cell.cellType = CellType::BOX;
            player.move(_dRow, _dCol);
            isMove = true;
            isPush = true;
        }
        else if(next_cell.cellType == CellType::TARGET)
        {
            cell.cellType = CellType::TARGET;
            next_cell.cellType = CellType::INTARGET;
            player.move(_dRow, _dCol);
            isMove = true;
            isPush = true;
        }
    }
    else
    {
        player.move(_dRow, _dCol);
        isMove = true;
        isPush = false;
    }

    //如果移动了，那么就把上一时刻的状态维护到栈中
    //并且更新label显示的数
    if(isMove)
    {
        state.push(State(nowRow, nowCol, isPush, nowFace));
        label->setText(QString::number(player.step));
    }

    //移动完成之后，更新状态
    cell.update();
    next_cell.update();
}

void MainWindow::set()
{
    //更新地图信息
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            map.Arr[i][j].cellType = origin_map.Arr[i][j].cellType;
            map.Arr[i][j].update();
        }
    }
    //更新玩家信息
    player = origin_player;

    //将栈清空，并重新初始化
    state.clear();
    state.push(State(player, false));
}

void MainWindow::callback()
{
    if(state.size() <= 1) return;
    State last_state = state.pop();

    //更新人物状态
    int now_face = player.face;
    Coordinate now_pos = Coordinate(player.Row(), player.Col());
    player.face = last_state.face;
    player.posX = last_state.pos.col * length + leftMargin;
    player.posY = last_state.pos.row * length + topMargin;
    player.step--;

    //如果推了箱子，就更新箱子状态
    if(!last_state.isPush) return;
    int _dRow = 0; int _dCol = 0;   //箱子相对于人物的位置
    switch(now_face)
    {
    case Face::UP:
        _dRow = -1;
        break;
    case Face::DOWN:
        _dRow = 1;
        break;
    case Face::LEFT:
        _dCol = -1;
        break;
    case Face::RIGHT:
        _dCol = 1;
        break;
    }
    //玩家面对的位置
    Cell& facing_cell = map.Arr[now_pos.row + _dRow][now_pos.col + _dCol];
    //玩家当前所在的位置
    Cell& cur_cell = map.Arr[now_pos.row][now_pos.col];

    if(facing_cell.cellType == CellType::BOX)
    {
        facing_cell.cellType = CellType::EMPTY;
        cur_cell.cellType = (cur_cell.cellType == CellType::EMPTY) ?
            CellType::BOX : CellType::INTARGET;
    }
    else if(facing_cell.cellType == CellType::INTARGET)
    {
        facing_cell.cellType = CellType::TARGET;
        cur_cell.cellType = (cur_cell.cellType == CellType::EMPTY) ?
            CellType::BOX : CellType::INTARGET;
    }
    facing_cell.update();
    cur_cell.update();
}
