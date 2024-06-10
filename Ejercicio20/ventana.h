#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QImage>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class Ventana;
}
QT_END_NAMESPACE


class Ventana : public QWidget
{
    Q_OBJECT

public:
    Ventana(QWidget *parent = nullptr);
    ~Ventana();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void slot_descargaFinalizada(QNetworkReply* reply);

private:
    Ui::Ventana *ui;
    QPainter* painter;
    QNetworkAccessManager* manager;
    QImage im;


};

#endif // VENTANA_H
