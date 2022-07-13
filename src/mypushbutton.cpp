#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg)
{
    normalImgPath = normalImg;
    QPixmap pixmap;
    bool ret = pixmap.load(normalImgPath);
    assert(ret);    //是否成功加载图片
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width() * 0.75, pixmap.height() * 0.75));
}
