#ifndef ADMIN_H
#define ADMIN_H

#include <QObject>
#include "ventana.h"
#include "login.h"
#include "admindb.h"

class Admin : public QObject
{
    Q_OBJECT
public:
    static Admin* getInstance();
    void iniciar();

private:
    Ventana* ventana;
    static Admin* instance;
    explicit Admin(QObject *parent = nullptr);

private slots:
    void slot_validarUsuario(QString usuario, QString clave);

};

#endif // ADMIN_H
