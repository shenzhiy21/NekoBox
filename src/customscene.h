//自定义关卡界面

#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QMainWindow>
#include <QPixmap>
#include <QMouseEvent>
#include "cell.h"
#include "map.h"
#include "define.h"
#include "mypushbutton.h"
#include "coordinate.h"
#include "player.h"

enum CustomType
{
    empty,
    box,
    target,
    wall,
    player
};

class CustomScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit CustomScene(QWidget *parent = nullptr);
    int getCellType(int customType);
    void reset();       //重置

    //玩家
    Player player;
    bool playerExist = false;   //玩家是否已经被添加了

    //地图
    Map customMap;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

private:

    //按钮
    MyPushButton* boxBtn = nullptr;
    MyPushButton* wallBtn = nullptr;
    MyPushButton* playerBtn = nullptr;
    MyPushButton* targetBtn = nullptr;
    MyPushButton* checkBtn = nullptr; //确认
    MyPushButton* resetBtn = nullptr; //重置

    //图片
    QPixmap pix_box;
    QPixmap pix_wall;
    QPixmap pix_target;
    QPixmap help;
    QPixmap background;

    //鼠标
    QCursor cursor;

    //选择的格子种类
    int customType = CustomType::empty;

    //帮助界面
    bool showHelp = false;

    //自定义地图是否合法
    bool map_legal();

signals:
    void customCheck(); //确认完成自定义的信号
    void returnToMenu();    //回到主界面的信号
};

#endif // CUSTOMSCENE_H
