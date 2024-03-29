#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel label;
    QPixmap imagen("C:/Users/manue/OneDrive/Imágenes/argentina/La_bomboneraa.jpg");

    // Establecer la imagen en el QLabel
    label.setPixmap(imagen.scaled(label.size(), Qt::KeepAspectRatio));
    // Mostrar el QLabel de forma maximizada y centrado
    label.showMaximized();
    label.setAlignment(Qt::AlignCenter);

    // Cerrar la aplicación después de 3 segundos
    QTimer::singleShot(3000, &app, &QApplication::quit);

    return app.exec();
}
