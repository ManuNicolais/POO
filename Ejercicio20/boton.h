#ifndef BOTON_H
#define BOTON_H

#include <QWidget>

namespace Ui {
class Boton;
}

class Boton : public QWidget
{
    Q_OBJECT
public:
    explicit Boton(QWidget *parent = nullptr);
    ~Boton();

    enum Color { Azul, Verde, Magenta, Blanco,Violeta };

    void colorear(Color colorCode);
    void setText( QString texto );

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);


private:
    Ui::Boton *ui;

    Color currentColor;

signals:
    void signal_clic();
};

#endif // BOTON_H
