#include "usuarios.h"
#include "ui_Usuarios.h"
#include "login.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

Usuarios::Usuarios (QWidget *parent, login* loginWindow)
    : QWidget(parent)
    , ui(new Ui::Usuarios)
    , loginWindow(loginWindow)
{

    ui->setupUi(this);
    connect(ui->pbVolver, SIGNAL(clicked(bool)), this, SLOT(slot_Volver()));
    connect(ui->pbGuardar, SIGNAL(clicked(bool)), this, SLOT(slot_GuardarCambios()));

    // Conectar la bd
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database.sqlite");

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se puede conectar a la base de datos.");
    } else {
        cargarUsuarios();
    }

    //QTreeWidget
    connect(ui->twUsuarios, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(slot_ItemChanged(QTreeWidgetItem*, int)));
}

Usuarios::~Usuarios()
{
    db.close();
    delete ui;
}

void Usuarios::slot_Volver()
{
    this->close();
    if (loginWindow) {
        loginWindow->show();
    }
}

void Usuarios::cargarUsuarios()
{
    ui->twUsuarios->setColumnCount(4);
    QStringList headers = {"Usuario", "Nombre", "Apellido", "Email"};
    ui->twUsuarios->setHeaderLabels(headers);

    QSqlQuery query(db);
    query.prepare("SELECT usuario, nombre, apellido, mail FROM usuarios");

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Error al cargar los usuarios: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        QString usuario = query.value(0).toString();
        QString nombre = query.value(1).toString();
        QString apellido = query.value(2).toString();
        QString email = query.value(3).toString();

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->twUsuarios);
        item->setText(0, usuario);
        item->setText(1, nombre);
        item->setText(2, apellido);
        item->setText(3, email);

        // Hacer que las celdas sean editables
        for (int i = 0; i < 4; ++i) {
            item->setFlags(item->flags() | Qt::ItemIsEditable);
        }
    }
}

void Usuarios::slot_ItemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    actualizarUsuario(item);
}

void Usuarios::actualizarUsuario(QTreeWidgetItem *item)
{
    QString usuario = item->text(0);
    QString nombre = item->text(1);
    QString apellido = item->text(2);
    QString email = item->text(3);

    QSqlQuery query(db);
    query.prepare("UPDATE usuarios SET nombre = ?, apellido = ?, mail = ? WHERE usuario = ?");
    query.addBindValue(nombre);
    query.addBindValue(apellido);
    query.addBindValue(email);
    query.addBindValue(usuario);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Error al actualizar el usuario: " + query.lastError().text());
    }
}

void Usuarios::slot_GuardarCambios()
{
    db.commit();
    QMessageBox::information(this, "Guardado", "Cambios guardados correctamente.");
}
