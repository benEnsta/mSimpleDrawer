#ifndef MSIMPLEDRAWER_H
#define MSIMPLEDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>

#include <vector>
#include "math.h"

using namespace std;

class mSimpleDrawer : public QWidget
{
    Q_OBJECT
    
public:
    explicit mSimpleDrawer(double xmin, double xmax,
                            double ymin, double ymax,
                            QWidget *parent = 0);
    explicit mSimpleDrawer(QWidget *parent = 0);
    ~mSimpleDrawer();

    void Clean();
    void Center(double x,double y);
    void DrawArrow(double x,double y,
                   double dx,double dy,
                   double r=0.1,
                   QPen pen=QPen(Qt::black));
    void DrawBox(double xmin,double xmax,
                 double ymin,double ymax,
                 QPen pen, QBrush brush);
    void DrawEllipse(double cx, double cy,
                     double r,
                     QPen pen, QBrush brush);
    void DrawLine(double x1,double y1,
                  double x2,double y2,
                  QPen pen);
    void DrawPolygon(double x,double y,
                      double theta,
                      vector<double> X, vector<double> Y,
                      QPen pen, QBrush brush);
    void DrawRobot(double x,double y,
                   double theta);
    void DrawSailboat(double x,double y,
                      double theta, QColor colr,
                      double deltag, QColor colg,
                      double deltav,QColor colv);
    void DrawText(double x, double y,
                  QString s, QColor col);
    void Save(QString s);
    void setDrawingArea(double xmin, double xmax,
                       double ymin, double ymax);
    
private:
    QLabel *label;
    QPixmap *pixMap;
    double xMax,xMin,yMax,yMin;

    double xToPix(double x);
    double yToPix(double y);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // MSIMPLEDRAWER_H
