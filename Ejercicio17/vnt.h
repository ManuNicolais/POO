#ifndef VNT_H
#define VNT_H

#include <QWidget>

#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

namespace Ui {
class vnt;
}

class vnt : public QWidget
{

    Q_OBJECT

public:
    vnt(QWidget *parent = nullptr);
    ~vnt();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_descargaFinalizada(QNetworkReply *reply);

private:
    Ui::vnt *ui;
    QImage im;
    QNetworkAccessManager *manager;
};

#endif // VNT_H
