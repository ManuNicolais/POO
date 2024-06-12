#ifndef PANSER_H
#define PANSER_H

#include <QWidget>
#include <QRegularExpression>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QFileDialog>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class Panser;
}
QT_END_NAMESPACE

class Panser : public QWidget
{
    Q_OBJECT

public:
    Panser(QWidget *parent = nullptr);
    ~Panser();

    void getRecursos();

private:
    Ui::Panser *ui;

    QNetworkAccessManager* manager;

    QString HTML_almacen; //html_storage
    QString ruta_archivo; //filePath

    int pos_lista_CSS; //css_list_pos
    QStringList* lista_CSS; //css_list

    int pos_lista_JS; //js_list_pos
    QStringList* lista_JS; //js_list

    int pos_lista_img; //img_list_pos
    QStringList* lista_img; //img_list

    QImage img;

    int archivos_CSS_descargados; //css_files_downloaded
    int archivos_JS_descargados; //js_files_downloaded

private slots:
    void slot_descargar_HTML();
    void slot_descargar_archivos();
    void slot_HTML_descargado(QNetworkReply* reply);

    void slot_descargar_CSS();
    void slot_descargar_JS();
    void slot_descargar_IMG();

    void slot_CSS_descargado(QNetworkReply* reply);
    void slot_JS_descargado(QNetworkReply* reply);
    void slot_img_descargado(QNetworkReply* reply);

    void slot_QDialog_img_disco();
    void slot_imagen_obtenida(QString);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void signal_HTML_descargado();

    void signal_iniciar_descarga_CSS();
    void signal_CSS_descargado();

    void signal_iniciar_descarga_JS();
    void signal_JS_descargado();

    void signal_iniciar_descarga_img();
    void signal_IMG_descargado();
};

#endif // PANSER_H
