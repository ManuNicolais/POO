#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "ventana.h"

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

private:
    Ui::login *ui;

    Ventana* vnt;

private slots:
    void slot_verificar_usuario();
};
#endif // LOGIN_H
