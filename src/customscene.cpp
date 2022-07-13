#include "customscene.h"
#include <QPainter>

CustomScene::CustomScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1280, 1024);
    this->setWindowTitle("Custom");
    this->setWindowIcon(QIcon(":/res/Player_left.png"));

    //按钮初始化
    boxBtn = new MyPushButton(":/res/boxBtn.png");
    boxBtn->setParent(this);
    boxBtn->move(1130, 120);
    connect(boxBtn, &MyPushButton::clicked, [&](){
        customType = CustomType::box;
        this->update();
    });

    targetBtn = new MyPushButton(":/res/targetBtn.png");
    targetBtn->setParent(this);
    targetBtn->move(1130, 320);
    connect(targetBtn, &MyPushButton::clicked, [&](){
        customType = CustomType::target;
        this->update();
    });

    wallBtn = new MyPushButton(":/res/wallBtn.png");
    wallBtn->setParent(this);
    wallBtn->move(1130, 520);
    connect(wallBtn, &MyPushButton::clicked, [&](){
        customType = CustomType::wall;
        this->update();
    });

    playerBtn = new MyPushButton(":/res/playerBtn.png");
    playerBtn->setParent(this);
    playerBtn->move(1130, 720);
    connect(playerBtn, &MyPushButton::clicked, [&](){
        customType = CustomType::player;
        this->update();
    });

    checkBtn = new MyPushButton(":/res/checkBtn.png");
    checkBtn->setParent(this);
    checkBtn->move(200, 900);
    connect(checkBtn, &MyPushButton::clicked, [&](){
        if(map_legal()) emit this->customCheck();
    });

    resetBtn = new MyPushButton(":/res/resetBtn.png");
    resetBtn->setParent(this);
    resetBtn->move(600, 900);
    connect(resetBtn, &MyPushButton::clicked, [&](){
        this->reset();
    });

    //加载帮助界面
    help.load(":/res/help.png");

    //加载背景图片
    background.load(":/res/Background2.png");
}

void CustomScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //draw background begins here
    painter.drawPixmap(0, 0, 1280, 1024, background);
    //draw background ends here

    //draw map begins here
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            Cell curCell = customMap.Arr[i][j];
            QPixmap pix = curCell.pix;
            painter.drawPixmap(curCell.posX, curCell.posY, length, length, pix);
        }
    }

    //draw map ends here

    //draw player begins here
    if(playerExist)
    {
        painter.drawPixmap(player.posX, player.posY, player.width, player.height, player.pix);
    }
    //draw player ends here

    //draw rectangle begins here
    QRect rect;
    switch(customType)
    {
    case CustomType::box:
        rect = QRect(1130, 120, 150, 150);
        break;
    case CustomType::wall:
        rect = QRect(1130, 520, 150, 150);
        break;
    case CustomType::player:
        rect = QRect(1130, 720, 150, 150);
        break;
    case CustomType::target:
        rect = QRect(1130, 320, 150, 150);
        break;
    default:
        break;
    }

    painter.fillRect(rect, QBrush(QColor(255, 255, 255, 200)));
    //draw rectangle ends here

    //draw "help" begins here
    //帮助界面应该是最顶层的，需要最后绘制
    if(showHelp)
    {
        painter.fillRect(QRect(leftMargin, topMargin, COLUMN * length, ROW * length), QBrush(QColor(255, 255, 255, 200)));
        painter.drawPixmap((this->width() - help.width()) / 2, 232, help);
    }
    //draw "help" ends here
}

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_H)
    {
        showHelp = true;
    }
    if(event->key() == Qt::Key_Escape)
    {
        emit this->returnToMenu();
    }
    this->update();
}

void CustomScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_H)
    {
        showHelp = false;
    }
    this->update();
}

void CustomScene::mousePressEvent(QMouseEvent *event)
{
    QPoint cursorPos = event->pos();
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            Cell& curCell = customMap.Arr[i][j];
            if(cursorPos.x() > curCell.posX &&
                    cursorPos.x() < curCell.posX + length &&
                    cursorPos.y() > curCell.posY &&
                    cursorPos.y() < curCell.posY + length)
            {
                if(event->button() == Qt::LeftButton)
                {
                    if(getCellType(customType) > -1)
                    {
                        curCell.cellType = getCellType(customType);
                        curCell.update();
                        this->update();
                    }
                    //是玩家
                    else if(getCellType(customType) == -1 && !playerExist)
                    {
                        player.posX = leftMargin + j * length;
                        player.posY = topMargin + i * length;
                        playerExist = true;
                        curCell.cellType = CellType::EMPTY;
                        this->update();
                    }
                }
                else if(event->button() == Qt::RightButton)
                {
                    if(getCellType(customType) > -1)
                    {
                        curCell.cellType = CellType::EMPTY;
                        curCell.update();
                        this->update();
                    }
                    else if(getCellType(customType) == -1)
                    {
                        playerExist = false;
                        this->update();
                    }
                }
                break;
            }
        }
    }
}

int CustomScene::getCellType(int customType)
{
    switch(customType)
    {
    case CustomType::box:
        return CellType::BOX;
        break;
    case CustomType::wall:
        return CellType::WALL;
        break;
    case CustomType::target:
        return CellType::TARGET;
        break;
    case CustomType::empty:
        return CellType::EMPTY;
        break;
    case CustomType::player:
        return -1;  //-1代表玩家
        break;
    default:
        return -2;
        break;
    }
}

void CustomScene::reset()
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            Cell& cur_cell = customMap.Arr[i][j];
            cur_cell.cellType = CellType::EMPTY;
            cur_cell.update();
        }
    }
    playerExist = false;
    this->update();
}

bool CustomScene::map_legal()
{
    if(!playerExist) return false;
    int box_number = 0;     //箱子数量
    int target_number = 0;  //目标点数量
    //一个合法的地图的必要条件为：箱子数=目标点数>0
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            Cell curCell = customMap.Arr[i][j];
            if(curCell.cellType == CellType::BOX) box_number++;
            else if(curCell.cellType == CellType::TARGET) target_number++;
        }
    }
    if((box_number == target_number) && (box_number > 0)) return true;
    return false;
}
