#include "widget.h"
#include "helper.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include <QMouseEvent>


Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 400);
    deg = 1.8f;
    background = QBrush(QColor(14, 12, 14));
    circleBrush = QBrush(/*gradient*/QColor(12, 12, 12, 125));
    circlePen = QPen(Qt::black);
    circlePen.setColor(QColor(72, 121, 55, 125));
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(15);
    setMouseTracking(true);
}
bool valid{false};
bool renderPointerHelp{false};
QVector<QLine> lines;
QPoint p1{};
QPoint p2{};

void Widget::drawCross(const QPoint &p1,const QPoint &p2)
{
    QPen degrade  = QPen(QColor(18, 255, 253, 120));
    degrade.setWidth(2);
    painter.setPen(degrade);
    int x = p1.x();
    int y = p1.y();
    painter.drawLine(x-10, y, x+10, y);
    painter.drawLine(x, y-10, x, y+10);

    x = p2.x();
    y = p2.y();
    painter.drawLine(x-10, y, x+10, y);
    painter.drawLine(x, y-10, x, y+10);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    p2 = event->pos();
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        renderPointerHelp = false;
        lines.push_back(QLine(p1, p2));
    }
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        p1= event->pos();
        qDebug() << "RightButton";
        renderPointerHelp = true;
    }
    p2.setX(event->pos().x());
    p2.setY(event->pos().y());
}

void Widget::animate()
{
    deg += 1.8;
    if (deg >=360) {
        deg =1.8;
    }
    update();
}
void drawCircles(QPainter *painter)
{
    int radio{50};
    for (int var = 0; var < 5; ++var)
    {
        radio = var*100 +50;
        painter->drawEllipse(-radio/2, -radio/2, radio, radio);
    }

}
void drawNumbers(QPainter *painter)
{
    painter->drawText(QRect(-50, 0, 100, 50), Qt::AlignCenter, QStringLiteral("5"));
    painter->drawText(QRect(-50, 0, 100, 150), Qt::AlignCenter, QStringLiteral("15"));
    painter->drawText(QRect(-50, 0, 100, 250), Qt::AlignCenter, QStringLiteral("25"));
    painter->drawText(QRect(-50, 0, 100, 350), Qt::AlignCenter, QStringLiteral("35"));
}
void drawLines(QPainter *painter, const float deg)
{
    QPen degrade;
    auto m = 255.0*2 / 359;
    if (deg >= 0 && deg < 359.0/2)
    {
        auto x = (deg)/m;
        degrade = QPen(QColor(255, 0, 0, x));
        degrade.color().setAlpha(255);
    }
    else if(deg >= 359.0 /2 && deg < 359.0)
    {
        auto x = -1*(deg-359)*m;
        degrade = QPen(QColor(255, 0, 0, x));
    }
    degrade.setWidth(3);
    painter->setPen(degrade);
    painter->drawLine(0, 0,
                      350 * qCos(qDegreesToRadians(deg)),
                      350 * qSin(qDegreesToRadians(deg)));
}
void drawBox(QPainter *painter, int x, int y, int w, int h)
{
    QPen r = QPen(QColor(18, 255, 253, 120));
    r.setWidth(1);
    painter->setPen(r);

    painter->setPen(QColor(18, 255, 253, 100));
    uint k {5};
    //box
    painter->drawRect(QRect(x, y, w, h));
    //lines
    painter->drawLine(x-k, y, x+w+k, y);
    painter->drawLine(x-k, y+h, x+w+k, y+h);
    painter->drawLine(x, y-k, x, y+h+k);
    painter->drawLine(x+w, y-k, x+w, y+h+k);

    r.setWidthF(2.5);
    painter->setPen(r);
    //corners u-l
    painter->drawLine(x, y, x+2*k, y);
    painter->drawLine(x, y, x, y+2*k);
//    //corners d-l
    painter->drawLine(x, y+h, x, y+h-2*k);
    painter->drawLine(x, y+h, x+2*k, y+h);

//    //corners u-r
    painter->drawLine(x+w, y, x+w-2*k, y);
    painter->drawLine(x+w, y, x+w, y+2*k);
//    //corners u-l
    painter->drawLine(x+w, y+h, x+w-2*k, y+h);
    painter->drawLine(x+w, y+h, x+w, y+h-2*k);
}
void drawLinesCompass(QPainter *painter)
{
    painter->translate(-200, -200);

    painter->drawLine(0, 0, 400, 400);
    painter->drawLine(0, 400, 400, 0);
    painter->drawLine(0, 200, 400, 200);
    painter->drawLine(200, 0, 200, 400);

    painter->translate(200, 200);

    //
    for (int var = 0; var < 8; ++var) {

    painter->drawLine(0, 0,
                      300 * qCos(qDegreesToRadians(22.5+var*45)),
                      300 * qSin(qDegreesToRadians(22.5+var*45)));
    }

//    painter->rotate(5.0);
//    painter->drawLine(200, 0, 400, 0);
//    painter->rotate(-5.0);
//    painter->translate(-200, -200);
//    painter->translate(200, 200);
}
void Widget::paintEvent(QPaintEvent */*event*/)
{
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(0,0,400,400, background);
    painter.translate(200, 200);

    painter.setPen(circlePen);

    drawCircles(&painter);
    drawLinesCompass(&painter);
    drawLines(&painter, deg);

    painter.setPen(textPen);
    painter.setFont(textFont);
    drawNumbers(&painter);

    painter.translate(-200, -200);

    drawBox(&painter, 10, 10, 180, 50);

    drawBox(&painter, 100, 100, 100, 100);
    drawBox(&painter, 220, 250, 100, 80);
    //

    if (renderPointerHelp)
    {
        drawCross(p1, p2);
        painter.drawLine(p1, p2);
    }

    for (QLine& l : lines)
    {
        painter.drawLine(l);
    }

    QBrush brush(QColor(18, 255, 253, 55), Qt::CrossPattern);
    painter.fillRect(220,250,100,80, brush);

    painter.drawText(220,250,100,80,Qt::AlignCenter, "öúüñß34€");
    QPixmap qp = QPixmap(":/img/button-push.png");
    qp.scaled(32,32);

    painter.drawPixmap(300, 300, qp);
    painter.end();
}
