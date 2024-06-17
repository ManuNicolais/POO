#include "ventana.h"
#include "ui_ventana.h"

#include <QPainter>

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
    , manager(new QNetworkAccessManager (this))
{
    ui->setupUi(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargado(QNetworkReply*)));

    QString sURL = "https://oneftbl-cms.imgix.net/https%3A%2F%2Ffulbodivino.wordpress.com%2Fwp-content%2Fuploads%2F2024%2F03%2Fbombonera-boca.webp?auto=format%2Ccompress&crop=faces&dpr=2&fit=crop&h=210&q=25&w=280&s=eaf4b572bd25c189c3203eb4916b727e";
    manager->get(QNetworkRequest(QUrl(sURL)));
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if( !im.isNull()){
    painter.drawImage(0, 0, im.scaled(this->width(), this->height()));
    }
}

void Ventana::slot_descargado(QNetworkReply *reply)
{
    im = QImage::fromData(reply->readAll());
    this->repaint();
}
