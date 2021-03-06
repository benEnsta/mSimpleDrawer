#include "msimpledrawer.h"

#include <QDebug>

mSimpleDrawer::mSimpleDrawer(double xmin, double xmax,
                               double ymin, double ymax,
                               QWidget *parent) :
    QWidget(parent),
    xMax(xmax), xMin(xmin),
    yMax(ymax), yMin(ymin)
{
    label = new QLabel(this);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->resize(size());

    pixMap = new QPixmap(this->size());
    Clean();
}

mSimpleDrawer::mSimpleDrawer(QWidget *parent):
    QWidget(parent),
    xMax(10), xMin(-10),
    yMax(10), yMin(-10)
{
    label = new QLabel(this);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->resize(size());

    pixMap = new QPixmap(this->size());
    Clean();
}

mSimpleDrawer::~mSimpleDrawer()
{
    delete pixMap;
    delete label;
}

void mSimpleDrawer::paintEvent(QPaintEvent *)
{
    label->setPixmap(*pixMap);
}

void mSimpleDrawer::resizeEvent(QResizeEvent *)
{
    label->resize(size());
    QSize s = label->size();
    QPixmap tmp((pixMap->scaled(s,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    pixMap->swap(tmp);
}

double mSimpleDrawer::xToPix(double x)
{
    double echx = pixMap->width()/(xMax-xMin);
    return (x-xMin)*echx;
}

double mSimpleDrawer::yToPix(double y)
{
    double echy = pixMap->height()/(yMax - yMin);
    return pixMap->height() - (y-yMin)*echy;
}

void mSimpleDrawer::Clean()
{
    QPainter p(pixMap) ;
    QRect dim = p.window() ;
    p.setPen(QPen(Qt::red, 4)) ;
    p.setBrush(QBrush(Qt::white)) ;
    p.drawRect(dim) ;
}

void mSimpleDrawer::Center(double x, double y)
{
    double Rx=(xMax-xMin)/2.0;
    double Ry=(yMax-yMin)/2.0;
    xMin=x-Rx;    xMax=x+Rx;
    yMin=y-Ry;    yMax=y+Ry;
}

void mSimpleDrawer::DrawArrow(double x, double y,
                               double dx, double dy,
                               double r, QPen pen)
{
    double x2=x+dx;
    double y2=y+dy;
    double a=3.14-1.0;
    double px=x2+r*(cos(a)*dx-sin(a)*dy);    // cot de pointe
    double py=y2+r*(sin(a)*dx+cos(a)*dy);
    double qx=x2+r*(cos(-a)*dx-sin(-a)*dy);  // autre cot de pointe
    double qy=y2+r*(sin(-a)*dx+cos(-a)*dy);

    QPainter p(pixMap);
    p.setPen(pen);
    p.drawLine(xToPix(x),yToPix(y),xToPix(x2),yToPix(y2));
    p.drawLine(xToPix(x2),yToPix(y2),xToPix(px),yToPix(py));
    p.drawLine(xToPix(x2),yToPix(y2),xToPix(qx),yToPix(qy));
}

void mSimpleDrawer::DrawBox(double xmin, double xmax,
                             double ymin, double ymax,
                             QPen pen, QBrush brush)
{
    QPolygonF box;
    box << QPointF(xToPix(xmin),yToPix(ymin))
         << QPointF(xToPix(xmax),yToPix(ymin))
         << QPointF(xToPix(xmax),yToPix(ymax))
         << QPointF(xToPix(xmin),yToPix(ymax));

    QPainter p(pixMap);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawPolygon(box);
}

void mSimpleDrawer::DrawEllipse(double cx, double cy, double r,
                                 QPen pen, QBrush brush)
{
    QPainter p(pixMap);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawEllipse(xToPix(cx-r),yToPix(cy+r),
                  xToPix(cx+r)-xToPix(cx-r),yToPix(cy-r)-yToPix(cy+r));
}

void mSimpleDrawer::DrawLine(double x1, double y1,
                              double x2, double y2,
                              QPen pen)
{
    QPainter p(pixMap);
    p.setPen(pen);
    p.drawLine(xToPix(x1),yToPix(y1),xToPix(x2),yToPix(y2));
}

void mSimpleDrawer::DrawPolygon(double x, double y,
                                  double theta,
                                  vector<double> X, vector<double> Y,
                                  QPen pen, QBrush brush)
{
    QPolygonF poly;
    for (int k=0;k<X.size();k++)
    {
        double x1=x+cos(theta)*X[k]-sin(theta)*Y[k];
        double y1=y+sin(theta)*X[k]+cos(theta)*Y[k];
        poly << QPointF(xToPix(x1),yToPix(y1));
    }

    QPainter p(pixMap);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawPolygon(poly);
}

void mSimpleDrawer::DrawRobot(double x, double y, double theta)
{
    vector<double> X,Y;
    X.push_back(0); Y.push_back(-1);
    X.push_back(3); Y.push_back(0);
    X.push_back(0); Y.push_back(1);
    DrawPolygon(x,y,theta,X,Y, QPen(Qt::blue), QBrush(Qt::black));
}

void mSimpleDrawer::DrawSailboat(double x, double y,
                                  double theta, QColor colr,
                                  double deltag, QColor colg,
                                  double deltav, QColor colv)
{
    double a=0.8;
    vector<double> Xc,Yc;                //coque
    Xc.push_back(-a);  Yc.push_back(-a);
    Xc.push_back(4*a); Yc.push_back(0);
    Xc.push_back(-a);  Yc.push_back(a);
    Xc.push_back(-a);  Yc.push_back(-a);
    DrawPolygon(x,y,theta,Xc,Yc,colr, colr);

    vector<double> Xr,Yr;  //gouvernail
    Xr.push_back(-2*a);  Yr.push_back(0);
    Xr.push_back(0);   Yr.push_back(0);
    DrawPolygon(x-a*cos(theta),y-a*sin(theta),
                 theta+deltag,Xr,Yr,QPen(colg),QBrush(colg));

    vector<double> Xv,Yv;  //voile
    Xv.push_back(-5*a);  Yv.push_back(0);
    Xv.push_back(0);     Yv.push_back(0);
    DrawPolygon(x+3*a*cos(theta),y+3*a*sin(theta),
                 theta+deltav,Xv,Yv,colv,colv);

}

void mSimpleDrawer::DrawText(double x, double y,
                              QString s, QColor col)
{
    QPainter p(pixMap);
    p.setPen(QPen(col));
    p.setFont(QFont("Arial"));
    p.drawText((int)xToPix(x),(int)yToPix(y),s);
}

void mSimpleDrawer::Save(QString s)
{
    pixMap->save(s+".png","PNG",100);
}

void mSimpleDrawer::setDrawingArea(double xmin, double xmax,
                                   double ymin, double ymax)
{
    xMax=xmax;
    xMin=xmin;
    yMax=ymax;
    yMin=ymin;
}
