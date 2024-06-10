#include "ventana.h"
#include "ui_ventana.h"

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this); // Llama a setupUi antes de acceder a ui

    // Conectar señales y slots
    connect(ui->pbBuscar, &QPushButton::clicked, this, &Ventana::slot_descargar_html);
    connect(manager, &QNetworkAccessManager::finished, this, &Ventana::slot_html_descargado);
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::finalizar_Programa()
{
    QApplication::quit();
}

void Ventana::slot_descargar_html()
{
    if (!(ui->leURL->text().isEmpty())) {
        QNetworkRequest request(QUrl(ui->leURL->text()));
        manager->get(request);
    }
}

void Ventana::slot_html_descargado(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray htmlData = reply->readAll();
        ui->teHTML->setPlainText(QString::fromUtf8(htmlData));
    } else {
        ui->teHTML->setPlainText("Error: " + reply->errorString());
    }
    reply->deleteLater();
}
