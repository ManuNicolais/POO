#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

namespace Ui {
class Ventana;
}

class Ventana: public QWidget
{

    Q_OBJECT

public:
    Ventana(QWidget *parent = nullptr);
    ~Ventana();

private:
    Ui::Ventana *ui;
    QNetworkAccessManager* manager;

private slots:
    void finalizar_Programa();
    void slot_descargar_html();
    void slot_html_descargado(QNetworkReply* reply);
};

#endif // VENTANA_H
