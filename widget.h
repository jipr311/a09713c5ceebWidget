#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPen>
#include <QPainter>

//! [0]
class Helper;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent);

public slots:
    void animate();
    void drawCross(const QPoint &p1, const QPoint &p2);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    float deg;
    QBrush background;
    QBrush circleBrush;
    QPen circlePen;
    QPen textPen;
    QFont textFont;

    QPainter painter;
};
//! [0]

#endif
