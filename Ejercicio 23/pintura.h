#ifndef PINTURA_H
#define PINTURA_H

#include <QWidget>

#include <QMouseEvent>
#include <QColorDialog>
#include <QPainter>

#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Pintura;
}
QT_END_NAMESPACE

class Pintura : public QWidget
{
    Q_OBJECT

public:
    Pintura(QWidget *parent = nullptr);
    ~Pintura();

private:
    Ui::Pintura *ui;
    QImage image;
    QPoint lastPoint;
    int penSize;
    QColor penColor;

    void drawLineTo(const QPoint &endPoint);
    void clearCanvas();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;


};
#endif // PINTURA_H
