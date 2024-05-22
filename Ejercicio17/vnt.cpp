#include "vnt.h"
#include "ui_ventana.h"

#include <QPainter>

vnt::vnt(QWidget *parent)
    : QWidget(parent)
    , manager(new QNetworkAccessManager(this))
{

    connect(manager, &QNetworkAccessManager::finished, this, &vnt::slot_descargaFinalizada);

    QString sUrl = "https://media.istockphoto.com/id/1657084255/es/foto/buenos-aires-argentina-28-de-mayo-de-2023-foto-a%C3%A9rea-al-atardecer-en-el-estadio-de-boca.jpg?s=612x612&w=0&k=20&c=oRdHSUmF42z-Y5HIvOpPyV-79NZ2li8V3r3zkOmfNvQ=";
    manager->get(QNetworkRequest(QUrl(sUrl)));

}

vnt::~vnt()
{
    delete ui;
}


void vnt::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!im.isNull()) {
        painter.drawImage(0, 0, im.scaled(this->width(), this->height()));
    }
}

void vnt::slot_descargaFinalizada(QNetworkReply *reply)
{
    im = QImage::fromData(reply->readAll());
    this->repaint();
}
