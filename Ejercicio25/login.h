#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QImage>
#include <QPainter>

//intentos
#include <QTimer>
#include <QMessageBox>

//adminDB
#include "admindb.h"

//ventana
#include "ventana.h"
//usuarios
#include "usuarios.h"


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

signals:
    void mostrarVentanaPrincipal();

private:
    Ui::login *ui;

    QNetworkAccessManager* manager;
    QImage im;

//intentos
    int intentosFallidos;
    QTimer *timerBloqueo;
    int tiempoRestante;

//adminDB
    AdminDB * adminDB;

//ventana
    Ventana* ventana;
//usuarios
    Usuarios* usuarios;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_verificar_usuario();
    void slot_descargaFinalizada(QNetworkReply* reply);

//intentos
    void deshabilitarControles();
    void desbloquearUsuario();
    void actualizarTiempoRestante();
    void actualizarBoton();

//registrar
    void slot_Registrar();
};
#endif // LOGIN_H
