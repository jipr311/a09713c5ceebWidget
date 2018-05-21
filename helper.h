#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QVector>

class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event, float deg);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;

    QVector<uint> vector;
};

#endif
