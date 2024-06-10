#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QImage>
#include <QPainter>

#include <weather.h>

//intentos
#include <QTimer>
#include <QMessageBox>

//adminDB

#include "admindb.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

    //enumeracion
    enum Modo { Temp, ImagenFondo, Sqlite };
    void setModo( Modo modo );

private:
    Ui::login *ui;

    QNetworkAccessManager* manager;
    QImage im;

//temp
    Weather* weather;

//intentos
    int intentosFallidos;
    QTimer *timerBloqueo;
    int tiempoRestante;

//adminDB
    AdminDB * adminDB;

//numeracion
    Modo modo;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_verificar_usuario();
    void slot_esconderTemperatura();
    void slot_descargaFinalizada(QNetworkReply* reply);
    void slot_actualizarTemperatura(const QString &temperatura);

//intentos
    void deshabilitarControles();
    void desbloquearUsuario();
    void actualizarTiempoRestante();
    void actualizarBoton();
};
#endif // LOGIN_H
