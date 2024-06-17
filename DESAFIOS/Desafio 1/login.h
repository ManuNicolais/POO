#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "ventana.h"

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

private slots:
    void slot_validar();

private:
    Ui::Login *ui;

    Ventana *ventana;
};
#endif // LOGIN_H
