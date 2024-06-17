#include "boton.h"
#include "ui_boton.h"

#include <QPainter>
#include <QColor>

Boton::Boton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Boton)
    , color(Boton::Blanco)
{
    ui->setupUi(this);
}

Boton::~Boton()
{
    delete ui;
}

void Boton::setTexto(QString texto)
{
    ui->lTexto->setText(texto);
}


void Boton::setColor(Color color)
{
    this->color = color;
    this->repaint();
}


void Boton::mousePressEvent(QMouseEvent *event)
{
    emit signal_clicked();
}

void Boton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    switch(color)
    {
        case Boton::Rojo:
            painter.fillRect(0, 0, this->width(), this->height(), QColor(255, 0, 0));
            break;
        case Boton::Verde:
            painter.fillRect(0, 0, this->width(), this->height(), QColor(0, 255, 0));
            break;
        case Boton::Azul:
            painter.fillRect(0, 0, this->width(), this->height(), QColor(0, 0, 255));
            break;
        case Boton::Blanco:
            painter.fillRect(0, 0, this->width(), this->height(), QColor(255,255,255));
            break;
    }


}
