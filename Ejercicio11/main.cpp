#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Crear un objeto de la clase QLabel
    QLabel label("Etiqueta");
    label.show();

    // Crear un objeto de la clase QWidget
    QWidget widget;
    widget.show();

    // Crear un objeto de la clase QPushButton
    QPushButton button("Botón");
    button.show();

    // Crear un objeto de la clase QLineEdit
    QLineEdit lineEdit;
    lineEdit.show();

    return app.exec();
}
