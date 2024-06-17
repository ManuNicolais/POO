#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
    , ventana(new Ventana)
{
    ui->setupUi(this);
    ui->leUsuario->setFocus();

    connect(ui->pbValidar, SIGNAL(clicked()), this, SLOT(slot_validar()));
    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validar()));

}

Login::~Login()
{
    delete ui;
}

void Login::slot_validar()
{
    if(ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234")
    {
        ventana->show();
        this->close();
    }
    else
    {
        this->close();
    }
}
