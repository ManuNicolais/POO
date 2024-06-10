#include "ventana.h"
#include "ui_ventana.h"

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(slot_descargaFinalizada(QNetworkReply * )));
    QNetworkRequest request(QUrl("https://freshprompts-blog-images.s3.amazonaws.com/background-drawing-ideas/color.jpg"));
    manager->get(request);

    ui->BotonSalir->setText( "Salir" );
    ui->BotonSalir->colorear(Boton::Azul);

    ui->boton1->setText("Mi dentista");
    ui->boton1->colorear(Boton::Magenta);

    ui->boton2->setText("Visitas");
    ui->boton2->colorear(Boton::Verde);

    ui->boton3->setText("Tecnicas de higiene");
    ui->boton3->colorear(Boton::Blanco);

    ui->boton4->setText("Mi boca");
    ui->boton4->colorear(Boton::Violeta);

    connect(ui->BotonSalir, SIGNAL(signal_clic()), this, SLOT(close()));
}

void Ventana::slot_descargaFinalizada(QNetworkReply* reply) {
    im = QImage::fromData(reply->readAll());
    this->repaint();
    this->show();

}

void Ventana::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(!im.isNull()) {
        painter.drawImage(0, 0, im.scaled(this->size()));
    }
}


Ventana::~Ventana()
{
    delete ui;
}
