#ifndef BOTON_H
#define BOTON_H

#include <QWidget>

#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Boton;
}
QT_END_NAMESPACE

class Boton : public QWidget
{
    Q_OBJECT

public:
    Boton(QWidget *parent = nullptr);
    ~Boton();

    enum Color {Rojo, Verde, Azul, Blanco};

    void setTexto(QString texto);
    void setColor(Color color);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

signals:
    void signal_clicked();

private:
    Ui::Boton *ui;

    Color color;
};
#endif // BOTON_H
