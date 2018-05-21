#include "widget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QSlider>

Window::Window()
{
    setWindowTitle(tr("2D Painting"));

    Widget *native = new Widget( this);
    QLabel *nativeLabel = new QLabel(tr("Native"));

    nativeLabel->setAlignment(Qt::AlignHCenter);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(native, 0, 0);
    layout->addWidget(nativeLabel, 1, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, native, &Widget::animate);
    timer->start(1);
}
