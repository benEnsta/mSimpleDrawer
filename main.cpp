#include <QtGui/QApplication>
#include "intervaldrawer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IntervalDrawer w(-10,10,-10,10);
    w.show();

    w.DrawBox(0,5,0,10,QPen(Qt::darkRed),QBrush(Qt::red));
    w.DrawArrow(0,0,5,2);
    w.DrawEllipse(0,0,2,QPen(Qt::darkBlue),QBrush(Qt::blue));
    w.DrawLine(-10,-10,-5,-5,QPen(Qt::darkBlue));
    w.DrawRobot(5,5,0);
    w.DrawText(-5,5,"Saad",Qt::blue);
    w.Save("test");

    return a.exec();
}
