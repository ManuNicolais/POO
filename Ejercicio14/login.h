#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QImage>

#include <QTimer>
#include <QMessageBox>

class Login : public QWidget{
    Q_OBJECT

private:
    QLabel *lUsuario, *lClave, *lTitulo;
    QLineEdit *leUsuario, *leClave;
    QPushButton *pbEntrar;
    QGridLayout *layout;
    QImage im;

    QNetworkAccessManager *manager;

//temperatura
    QLabel *lTemperatura;
    QPushButton *pbMostrarTemperatura;

//intentos
    int intentosFallidos;
    QTimer *timerBloqueo;
    int tiempoRestante;

public:
    Login();
    virtual ~Login();

private slots:
    void slot_validarUsuario();
    void slot_descargaFinalizada(QNetworkReply *reply);

    void slot_mostrarOcultarTemperatura();

    void deshabilitarControles();
    void desbloquearUsuario();
    void actualizarTiempoRestante();
    void actualizarBoton();

protected:
    void paintEvent(QPaintEvent *) override;

};

#endif // LOGIN_H
