#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , vnt ( new Ventana)
{
    ui->setupUi(this);


    connect(ui->pbIngresar, SIGNAL(clicked(bool)), this, SLOT(slot_verificar_usuario()));

    //ingresar con "enter"
    ui->pbIngresar->setDefault(true);
    connect(ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_verificar_usuario()));
    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_verificar_usuario()));
}

void login::slot_verificar_usuario()
{

    if (ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234") {
        qDebug() << "Usuario valido";
        this->close();

        //Ventana* form_point = new Ventana;

        vnt->show();
    } else {
        ui->leClave->clear();
    }

}

login::~login()
{
    delete ui;
}
