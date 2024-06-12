#ifndef USUARIOS_H
#define USUARIOS_H

#include <QWidget>

#include <QSqlDatabase>

#include <QTreeWidget>

namespace Ui {
class Usuarios;
}

class login;

class Usuarios: public QWidget
{
    Q_OBJECT

public:
    explicit Usuarios(QWidget *parent = nullptr, login* loginWindow = nullptr);
    ~Usuarios();

private:
    Ui::Usuarios *ui;
    login* loginWindow;

    QSqlDatabase db;

    void cargarUsuarios();
    void actualizarUsuario(QTreeWidgetItem *item);

private slots:
    void slot_Volver();
    void slot_ItemChanged(QTreeWidgetItem *item, int column);
    void slot_GuardarCambios();

};

#endif // USUARIOS_H
