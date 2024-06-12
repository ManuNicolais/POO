#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

#include <QSqlDatabase>

namespace Ui {
class Ventana;
}

class login;

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr, login* loginWindow = nullptr);
    ~Ventana();

private:
    Ui::Ventana *ui;

    login* loginWindow;
    QSqlDatabase db;

private slots:
    void slot_Volver();

    void slot_RegistrarUsuario();

};

#endif // VENTANA_H
