#include "login.h"
#include "ui_login.h"

#include <QDebug>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);


    ui->leTemperatura->setReadOnly(true);//label en solo lectura


    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(slot_descargaFinalizada(QNetworkReply * )));
    QNetworkRequest request(QUrl("https://noticiasmundogaturroconcristianshak.files.wordpress.com/2013/01/mundo-gaturro-1_1360x768.jpg"));
    ui->leURL->setText("https://noticiasmundogaturroconcristianshak.files.wordpress.com/2013/01/mundo-gaturro-1_1360x768.jpg");
    manager->get(request);

    Weather* weather = new Weather(-31.4135, -64.18105); //latitud y longitud
    connect(weather, SIGNAL(weatherChanged(QString)), this, SLOT(slot_actualizarTemperatura(QString)));
    weather->obtenerTemperatura();

    connect(ui->pbEsconder, SIGNAL(clicked(bool)), this, SLOT(slot_esconderTemperatura()));
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
    adminDB = new AdminDB( this );
    qDebug() << "La base se abrio bien" << adminDB->conectar( "../database.sqlite" );

    /*
        1|cponce|1234|Carlos|Ponce
        2|moliva|1234|Mariana|Oliva
        3|mabuelo|1234|Miguel|Abuelo
        4|sfeilu|1234|Santiago|Feilú
        5|ccrastro|1234|Cristian|Crastro

    1|cgomez|1234|Carlos|Gomez|cgomez@gmail.com
    2|mgomez|4679|Marti|Gomez|mgomez@gmail.com
    3|dabril|2345|David|Abril|dabril@gmail.com
    4|fmanuel|1111|Manuel|Nicolais|fnicolais@gmail.com
    */
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

void login::slot_esconderTemperatura()
{
    if (ui->leTemperatura->echoMode() == QLineEdit::Normal) {
        ui->leTemperatura->setEchoMode(QLineEdit::NoEcho);
    } else {
        ui->leTemperatura->setEchoMode(QLineEdit::Normal);
    }
}

void login::slot_descargaFinalizada(QNetworkReply *reply)
{
    im = QImage::fromData(reply->readAll());
    this->repaint();
}

void login::slot_actualizarTemperatura(const QString &temperatura)
{
    ui->leTemperatura->setText(temperatura);
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
