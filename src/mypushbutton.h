#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

//自定义按钮类，继承自QT的QPushButton，用于实现按钮贴图等效果

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString normalImg);
    QString normalImgPath;  //按钮图片路径

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
