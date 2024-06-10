#include "pintura.h"
#include "ui_pintura.h"

Pintura::Pintura(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Pintura)
{
    ui->setupUi(this);

    image = QImage(this->size(), QImage::Format_RGB32);
    image.fill(Qt::white);
    penSize = 2;
    penColor = Qt::black;
}

Pintura::~Pintura()
{
    delete ui;
}


void Pintura::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void Pintura::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawLineTo(lastPoint);
    }
}

void Pintura::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) &&
        (event->pos() != lastPoint)) {
        drawLineTo(event->pos());
    }
}

void Pintura::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_R:
        penColor = Qt::red;
        break;
    case Qt::Key_A:
        penColor = Qt::blue;
        break;
    case Qt::Key_V:
        penColor = Qt::green;
        break;
    case Qt::Key_N:
        penColor = Qt::black;
        break;
    case Qt::Key_E:
        penColor = Qt::white;
        break;
    case Qt::Key_Escape:
        clearCanvas();
        break;
    default:
        break;
    }
}

void Pintura::wheelEvent(QWheelEvent *event)
{
    penSize += event->angleDelta().y() > 0 ? 1 : -1;

    penSize = qMax(1, penSize);
}

void Pintura::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penSize, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    lastPoint = endPoint;
    update();
}

void Pintura::clearCanvas()
{
    image.fill(Qt::white);
    update();
}
