#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
    , ventana ( new vnt)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(slot_descargaFinalizada(QNetworkReply * )));
    QNetworkRequest request(QUrl("https://media.istockphoto.com/id/1657084255/es/foto/buenos-aires-argentina-28-de-mayo-de-2023-foto-a%C3%A9rea-al-atardecer-en-el-estadio-de-boca.jpg?s=612x612&w=0&k=20&c=oRdHSUmF42z-Y5HIvOpPyV-79NZ2li8V3r3zkOmfNvQ="));
    ui->leURL->setText("https://media.istockphoto.com/id/1657084255/es/foto/buenos-aires-argentina-28-de-mayo-de-2023-foto-a%C3%A9rea-al-atardecer-en-el-estadio-de-boca.jpg?s=612x612&w=0&k=20&c=oRdHSUmF42z-Y5HIvOpPyV-79NZ2li8V3r3zkOmfNvQ=");
    manager->get(request);

    connect(ui->pbIniciar, SIGNAL(clicked(bool)), this, SLOT(slot_verificar_usuario()));
    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_verificar_usuario()));
}

void Login::slot_verificar_usuario() {
    if (ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234")  {
        QString temp(ui->leUsuario->text());
        this->close();

        ventana->show();
    }
    else  {
        ui->leClave->setText("");
    }
}

void Login::slot_descargaFinalizada(QNetworkReply* reply) {
    im = QImage::fromData(reply->readAll());
    this->repaint();
}

void Login::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if(!im.isNull()) {
        painter.drawImage(0, 0, im.scaled(this->size()));
    }
}

Login::~Login()
{
    delete ui;
    if (ventana) {
        delete ventana;
    }
}
