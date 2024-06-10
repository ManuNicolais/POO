#include "admindb.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlError>
#include <QCryptographicHash>
#include <QDebug>

AdminDB* AdminDB::instance = nullptr;

AdminDB::AdminDB(QObject* parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

AdminDB* AdminDB::getInstance()
{
    instance = instance ? instance : new AdminDB;
    return instance;
}

bool AdminDB::conectar(QString archivoSqlite)
{
    db.setDatabaseName(archivoSqlite);
    if (db.open()) {
        qDebug() << "Base de datos conectada: " << archivoSqlite;
        return true;
    } else {
        qDebug() << "Error al abrir la base de datos: " << db.lastError().text();
        return false;
    }
}

QSqlDatabase AdminDB::getDB()
{
    return db;
}

QStringList AdminDB::validarUsuario(QString usuario, QString clave)
{
    QStringList datosPersonales;

    if (!db.isOpen()) {
        qDebug() << "La base de datos no está abierta.";
        return datosPersonales;
    }

    QSqlQuery query(db);
    QString claveMd5 = QCryptographicHash::hash(clave.toUtf8(), QCryptographicHash::Md5).toHex();
    query.prepare("SELECT nombre, apellido FROM usuarios WHERE usuario = :usuario AND clave = :clave");
    query.bindValue(":usuario", usuario);
    query.bindValue(":clave", claveMd5);

    if (query.exec()) {
        while (query.next()) {
            QSqlRecord registro = query.record();
            datosPersonales << query.value(registro.indexOf("nombre")).toString();
            datosPersonales << query.value(registro.indexOf("apellido")).toString();
        }
    } else {
        qDebug() << "Error en la consulta de validación de usuario: " << query.lastError().text();
    }

    qDebug() << "Datos personales obtenidos: " << datosPersonales;
    return datosPersonales;
}
