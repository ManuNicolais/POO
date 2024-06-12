#include "login.h"
#include "ui_login.h"

#include <QDebug>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
    , ventana ( new Ventana(nullptr, this))
    , usuarios ( new Usuarios(nullptr, this))
{
    ui->setupUi(this);
    this->ui->leUsuario->setFocus();
    ui->leUsuario->setText("Usuario");

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(slot_descargaFinalizada(QNetworkReply * )));
    QNetworkRequest request(QUrl("https://noticiasmundogaturroconcristianshak.files.wordpress.com/2013/01/mundo-gaturro-1_1360x768.jpg"));
    manager->get(request);

    connect(ui->pbIngresar, SIGNAL(clicked(bool)), this, SLOT(slot_verificar_usuario()));

//intentos
    intentosFallidos = 0;
    tiempoRestante = 0;
    timerBloqueo = new QTimer(this);
    timerBloqueo->setSingleShot(true);
    connect(timerBloqueo, SIGNAL(timeout()), this, SLOT(desbloquearUsuario()));

//ingresar con "enter"
    ui->pbIngresar->setDefault(true);
    connect(ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_verificar_usuario()));
    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_verificar_usuario()));

//adminDB
    adminDB = AdminDB::getInstance();
    qDebug() << "La base se abrio bien" << adminDB->conectar("../database.sqlite");

//registrar
    connect(ui->pbRegistrar, SIGNAL(clicked(bool)), this, SLOT(slot_Registrar()));

}

login::~login()
{
    delete ui;
}

void login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(!im.isNull()) {
        painter.drawImage(0, 0, im.scaled(this->size()));
    }
}

void login::slot_verificar_usuario()
{

    // login
    //if (ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234") {
    //adminDB
    if (    adminDB->validarUsuario( "usuarios", ui->leUsuario->text(), ui->leClave->text() ) ){
        qDebug() << "Usuario valido";
        this->close();
        usuarios->show();

    } else {
        ui->leClave->clear();
        intentosFallidos ++;
        if (intentosFallidos >= 3) {
            QMessageBox::critical(this, "Error", "Demasiados intentos fallidos. Usuario bloqueado por 10 segundos.");
            deshabilitarControles();
            tiempoRestante = 10;
            timerBloqueo->start(10000);
            actualizarBoton();
        }
    }

}


void login::slot_descargaFinalizada(QNetworkReply *reply)
{
    im = QImage::fromData(reply->readAll());
    this->repaint();
}

void login::deshabilitarControles() {
    ui->leUsuario->setEnabled(false);
    ui->leClave->setEnabled(false);
    ui->pbIngresar->setEnabled(false);
}

void login::desbloquearUsuario() {
    ui->leUsuario->setEnabled(true);
    ui->leClave->setEnabled(true);
    ui->pbIngresar->setEnabled(true);
    intentosFallidos = 0;
    tiempoRestante = 0;
    ui->pbIngresar->setText("Entrar");
}

void login::actualizarTiempoRestante() {
    if (tiempoRestante > 0) {
        tiempoRestante--;
        actualizarBoton();
    }
}

void login::actualizarBoton() {
    ui->pbIngresar->setText(QString("Intentar de nuevo en %1 segundos").arg(tiempoRestante));
}

void login::slot_Registrar()
{
    this->close();
    ventana->show();
}
