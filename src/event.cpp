//该文件负责mainwindow类中的事件处理，包括键盘事件、鼠标事件等，不包括绘图事件

#include <mainwindow.h>
#include <QKeyEvent>

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_H)
    {
        tabPressedDown = true;
    }
    if(isGaming)
    {
        switch(event->key())
        {
        case Qt::Key_W:
            collision(-1, 0);
            break;
        case Qt::Key_A:
            collision(0, -1);
            break;
        case Qt::Key_S:
            collision(1, 0);
            break;
        case Qt::Key_D:
            collision(0, 1);
            break;
        case Qt::Key_R:
            this->set();
            break;
        case Qt::Key_Z:
            this->callback();
            break;
        case Qt::Key_Escape:
            this->returnToMenu();
            break;
        }

        //判断胜利与否
        if(map.Success())
        {
            success = true;
        }
    }
    this->update();
    label->setText(QString::number(player.step));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_H:
        tabPressedDown = false;
        break;
    }
    this->update();
}

void MainWindow::chooseLevel()
{
    this->hide();
    chooseScene->show();
    this->update();
}

void MainWindow::startGame()
{
    success = false;
    startBtn->hide();
    customBtn->hide();
    exitBtn->hide();
    isGaming = true;
    player.step = 0;
    if(customScene->playerExist) this->copy();
    this->update();
}

void MainWindow::copy()
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            Cell& cur_cell = map.Arr[i][j];
            cur_cell.cellType = customScene->customMap.Arr[i][j].cellType;
            if(i == 0 || i == ROW - 1 || j == 0 || j == COLUMN - 1)
                cur_cell.cellType = CellType::WALL;
            customScene->customMap.Arr[i][j].cellType = CellType::EMPTY;
            cur_cell.update();
        }
    }
    player.posX = customScene->player.posX;
    player.posY = customScene->player.posY;
    player.step = 0;

    //拷贝备用的地图和玩家
    origin_map = map;
    origin_player = player;
    customScene->playerExist = false;
}

void MainWindow::initGame()
{
    //场景初始化
    std::string filename = "map\\" + std::to_string(chooseScene->level) + ".txt";
    map.InitByFile(filename);
    player.reset(3, 4);

    //将初始信息入栈
    state.push(State(player, false));


    //拷贝游戏状态
    origin_map = map;
    origin_player = player;
}

void MainWindow::returnToMenu()
{
    //重置当前状态
    isChoosing = false;
    isGaming = false;
    isCustom = false;

    //恢复按钮
    startBtn->show();
    customBtn->show();
    exitBtn->show();

    //玩家位置重置
    player.reset(3, 4);
    state.clear();

    //步数显示关闭
    label->hide();

    this->update();
}
