#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QDebug>
#include <QtMath>

Helper::Helper()
{

    background = QBrush(QColor(14, 12, 14));
    circleBrush = QBrush(/*gradient*/QColor(12, 12, 12, 125));
    circlePen = QPen(Qt::black);
//rgb(72, 121, 55)
    circlePen.setColor(QColor(72, 121, 55, 125));
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(15);
    vector = {0};
}

void Helper::paint(QPainter *painter, QPaintEvent *event, float deg)
{

}
