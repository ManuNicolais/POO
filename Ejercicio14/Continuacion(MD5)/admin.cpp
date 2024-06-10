#include "admin.h"
#include <QDebug>

Admin* Admin::instance = nullptr;

Admin::Admin(QObject *parent) : QObject(parent), ventana(new Ventana())
{
    connect(Login::getInstance(), &Login::signal_solicitarValidacion, this, &Admin::slot_validarUsuario);
    connect(this->ventana, &Ventana::signal_volver, Login::getInstance(), &Login::show);
}

Admin* Admin::getInstance()
{
    instance = instance ? instance : new Admin();
    return instance;
}

void Admin::iniciar()
{
    Login::getInstance()->show();
}

void Admin::slot_validarUsuario(QString usuario, QString clave)
{
    qDebug() << "Intentando conectar a la base de datos...";
    if (AdminDB::getInstance()->conectar("../Ejercicio2/base.sqlite")) {
        qDebug() << "Conexión a la base de datos exitosa.";
        QStringList datosUsuario = AdminDB::getInstance()->validarUsuario(usuario, clave);
        if (!datosUsuario.isEmpty()) {
            qDebug() << "Usuario validado: " << datosUsuario;
            Login::getInstance()->hide();
            this->ventana->show();
        } else {
            qDebug() << "Usuario o clave incorrecta.";
        }
    } else {
        qDebug() << "Error al conectar a la base de datos.";
    }
}
