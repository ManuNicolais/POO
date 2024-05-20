#include "login.h"
#include <QPainter>

Login::Login() {
    lTitulo = new QLabel("Bienvenidos");
    lTitulo->setAlignment(Qt::AlignCenter);

    lUsuario = new QLabel("Usuario");
    lClave = new QLabel("Clave");
    leUsuario = new QLineEdit;
    leClave = new QLineEdit;
    leClave->setEchoMode( QLineEdit::Password );
    pbEntrar = new QPushButton("Entrar");
    layout = new QGridLayout;

    lTemperatura = new QLabel("Temperatura en Cordoba");
    pbMostrarTemperatura = new QPushButton("Temperatura");

    layout->addWidget(lTitulo, 0, 0, 1, 3);
    layout->addWidget(lUsuario, 1, 0, 1, 1);
    layout->addWidget(lClave, 2, 0, 1, 1);
    layout->addWidget(leUsuario, 1, 1, 1, 2);
    layout->addWidget(leClave, 2, 1, 1, 2);
    layout->addWidget(pbEntrar, 3, 1, 1, 1);


    layout->addWidget(lTemperatura, 4, 0, 1, 3);
    layout->addWidget(pbMostrarTemperatura, 5, 0, 1, 3);


    this->setLayout(layout);

    connect(pbEntrar, SIGNAL(pressed()), this, SLOT(slot_validarUsuario()));
    connect(leClave, SIGNAL(returnPressed()), this, SLOT(slot_validarUsuario()));

//imagen
    manager = new QNetworkAccessManager( this );
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(slot_descargaFinalizada(QNetworkReply *)));
    QNetworkRequest request(QUrl("https://noticiasmundogaturroconcristianshak.files.wordpress.com/2013/01/mundo-gaturro-1_1360x768.jpg"));
    manager->get(request);

//temperatura
    connect(pbMostrarTemperatura, SIGNAL(pressed()), this, SLOT(slot_mostrarOcultarTemperatura()));

//intentos
    intentosFallidos = 0;
    tiempoRestante = 0;
    timerBloqueo = new QTimer(this);
    timerBloqueo->setSingleShot(true);
    connect(timerBloqueo, SIGNAL(timeout()), this, SLOT(desbloquearUsuario()));
}

void Login::slot_validarUsuario() {

    if (leUsuario->text() == "admin" && leClave->text() == "1234") {
        qDebug() << "Usuario valido";
        this->close();
    } else {
        leClave->clear();
        intentosFallidos++;
        if (intentosFallidos >= 3) {
            QMessageBox::critical(this, "Error", "Demasiados intentos fallidos. Usuario bloqueado por 10 segundos.");
            deshabilitarControles();
            tiempoRestante = 10;
            timerBloqueo->start(10000);
            actualizarBoton();
        }
    }
}

void Login::slot_descargaFinalizada(QNetworkReply *reply){
    im = QImage::fromData(reply->readAll());
    this->repaint();
}

void Login::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if(!im.isNull()){
       painter.drawImage(0, 0, im.scaled(this->size()));
    }
}

void Login::slot_mostrarOcultarTemperatura() {
    lTemperatura->setVisible(!lTemperatura->isVisible());
}

void Login::deshabilitarControles() {
    leUsuario->setEnabled(false);
    leClave->setEnabled(false);
    pbEntrar->setEnabled(false);
}

void Login::desbloquearUsuario() {
    leUsuario->setEnabled(true);
    leClave->setEnabled(true);
    pbEntrar->setEnabled(true);
    intentosFallidos = 0;
    tiempoRestante = 0;
    pbEntrar->setText("Entrar");
}

void Login::actualizarTiempoRestante() {
    if (tiempoRestante > 0) {
        tiempoRestante--;
        actualizarBoton();
    }
}

void Login::actualizarBoton() {
    pbEntrar->setText(QString("Intentar de nuevo en %1 segundos").arg(tiempoRestante));
}

Login::~Login() {
    delete lTitulo;
    delete lUsuario;
    delete lClave;
    delete leUsuario;
    delete leClave;
    delete pbEntrar;
    delete layout;
    delete manager;

}
