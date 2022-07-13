//选择关卡界面

#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include <QPixmap>
#include "define.h"

const int LEVEL_SIZE = 20;

class ChooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = nullptr);
    int level = -1;         //第几关

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);

private:
    QPixmap background;

signals:
    void startGame();
    void returnToMenu();
};

#endif // CHOOSESCENE_H
