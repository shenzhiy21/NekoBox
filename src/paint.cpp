//该文件负责mainwindow类中的绘图事件处理

#include <mainwindow.h>
#include <QPainter>

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //绘制背景
    painter.drawPixmap(0, 0, 1280, 1024, background);

    if(isGaming) gamePaintEvent(&painter);

    //draw "help" begins here
    //帮助界面应该是最顶层的，需要最后绘制
    if(tabPressedDown && (isGaming || isCustom))
    {
        painter.fillRect(QRect(leftMargin, topMargin, COLUMN * length, ROW * length), QBrush(QColor(255, 255, 255, 200)));
        painter.drawPixmap((this->width() - help.width()) / 2, 232, help);
    }
    //draw "help" ends here


}

void MainWindow::gamePaintEvent(QPainter* painter)
{
    QBrush brush(QColor(Qt::white), Qt::Dense4Pattern);

    //draw map begins here
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            Cell curCell = map.Arr[i][j];
            QPixmap pix = curCell.pix;
            painter->drawPixmap(curCell.posX, curCell.posY, length, length, pix);
        }
    }
    //draw map ends here


    //draw player begins here
    painter->drawPixmap(player.posX, player.posY, player.width, player.height, player.pix);
    //draw player ends here


    //draw steps begins here
    painter->setPen(Qt::white);
    QFont font("Microsoft Yahei", 20);
    painter->setFont(font);
    painter->drawText(50, 50, tr("step:"));
    label->show();
    //draw steps ends here


    //draw success begins here
    if(success)
    {
        painter->fillRect(QRect(leftMargin, topMargin, COLUMN * length, ROW * length), QBrush(QColor(255, 255, 255, 200)));
        painter->drawPixmap((this->width() - congrat.width())/2, 400, congrat);
    }
    //draw success ends here
}
