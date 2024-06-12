#include "ventana.h"
#include "ui_ventana.h"

#include "login.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

Ventana::Ventana(QWidget *parent, login* loginWindow)
    : QWidget(parent)
    , ui(new Ui::Ventana)
    , loginWindow(loginWindow)
{
    ui->setupUi(this);

    connect(ui->pbVolver, SIGNAL(clicked(bool)), this, SLOT(slot_Volver()));
    connect(ui->pbRegistrar, SIGNAL(clicked(bool)), this, SLOT(slot_RegistrarUsuario()));

    //conectar a bd
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database.sqlite");

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se puede conectar a la base de datos.");
    }
}

Ventana::~Ventana()
{
    db.close();
    delete ui;
}

void Ventana::slot_Volver()
{
    this->close();
    if (loginWindow) {
        loginWindow->show();
    }
}

void Ventana::slot_RegistrarUsuario()
{
    QString usuario = ui->leUsuario->text();
    QString clave = ui->leClave->text();
    QString nombre = ui->leNombre->text();
    QString apellido = ui->leApellido->text();
    QString email = ui->leEmail->text();

    if (usuario.isEmpty() || clave.isEmpty() || nombre.isEmpty() || apellido.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Todos los campos son obligatorios.");
        return;
    }

    QSqlQuery query(db);

    // Comprobar si el usuario ya existe
    query.prepare("SELECT COUNT(*) FROM usuarios WHERE usuario = :usuario");
    query.bindValue(":usuario", usuario);
    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Error", "Error al verificar el usuario.");
        return;
    }

    if (query.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Advertencia", "El usuario ya existe.");
        return;
    }

    // Insertar el nuevo usuario en la base de datos
    query.prepare("INSERT INTO usuarios (usuario, clave, nombre, apellido, mail) VALUES (:usuario, :clave, :nombre, :apellido, :email)");
    query.bindValue(":usuario", usuario);
    query.bindValue(":clave", clave);
    query.bindValue(":nombre", nombre);
    query.bindValue(":apellido", apellido);
    query.bindValue(":email", email);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Error al registrar el usuario: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Éxito", "Usuario registrado con éxito.");
        ui->leUsuario->clear();
        ui->leClave->clear();
        ui->leNombre->clear();
        ui->leApellido->clear();
        ui->leEmail->clear();
    }
}

