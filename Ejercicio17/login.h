#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QImage>
#include <QPainter>

#include "vnt.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;

    QNetworkAccessManager* manager;
    QImage im;

    vnt* ventana;

protected:
    void paintEvent(QPaintEvent *event) override;


private slots:
    void slot_verificar_usuario();
    void slot_descargaFinalizada(QNetworkReply* reply);
};
#endif // LOGIN_H
