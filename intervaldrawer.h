#ifndef INTERVALDRAWER_H
#define INTERVALDRAWER_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "math.h"

using namespace std;

namespace Ui {
class IntervalDrawer;
}

class IntervalDrawer : public QWidget
{
    Q_OBJECT
    
public:
    explicit IntervalDrawer(double xmin, double xmax,
                            double ymin, double ymax,
                            QWidget *parent = 0);
    ~IntervalDrawer();

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
    
private:
    Ui::IntervalDrawer *ui;
    QPixmap *pixMap;
    double xMax,xMin,yMax,yMin;

    double xToPix(double x);
    double yToPix(double y);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // INTERVALDRAWER_H
