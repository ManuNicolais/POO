#ifndef ADMINDB_H
#define ADMINDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>

#include<QDebug>

class AdminDB : public QObject
{
    Q_OBJECT
public:
    static AdminDB* getInstance(); // Método para obtener la instancia única
    bool conectar(QString archivoSqlite);
    QSqlDatabase getDB();
    bool validarUsuario(QString tabla, QString usuario, QString clave);

private:

    explicit AdminDB(QObject *parent = nullptr);
    static AdminDB* instance; // Instancia única
    QSqlDatabase db;

};

#endif // ADMINDB_H
