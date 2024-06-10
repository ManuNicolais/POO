#include "admindb.h"

#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

AdminDB::AdminDB(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase( "QSQLITE" );
}


bool AdminDB::conectar( QString archivoSqlite )  {
    db.setDatabaseName( archivoSqlite );

    if( db.open() )
        return true;

    return false;
}

QSqlDatabase AdminDB::getDB()  {
    return db;
}

bool AdminDB::validarUsuario(QString tabla, QString usuario, QString clave)
{
    if (db.isOpen()) {
        qDebug() << "apuntocaramelo";
        QSqlQuery query = db.exec( "SELECT nombre, apellido FROM " + tabla + " WHERE usuario = '" +
                                  usuario + "' AND clave = '" + clave + "'" );

        while( query.next() )  {
            qDebug() << "Consulta ejecutada";
            qDebug() << query.value( 0 ).toString() << " " << query.value( 1 ).toString();
            return true;
            }

    } else {
        qDebug() << "La base de datos no está abierta";
    }

    return false;
}
