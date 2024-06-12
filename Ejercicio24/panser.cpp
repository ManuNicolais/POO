#include "panser.h"
#include "ui_panser.h"

Panser::Panser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Panser)
    , archivos_CSS_descargados(0)
    , archivos_JS_descargados(0)
{
    ui->setupUi(this);

    connect(ui->pbGuardar, SIGNAL(clicked(bool)), this, SLOT(slot_descargar_HTML()));
    connect(this, SIGNAL(signal_HTML_descargado()), this, SLOT(slot_descargar_archivos()));
    connect(ui->pbDibujar, SIGNAL(clicked(bool)), this, SLOT(slot_QDialog_img_disco()));
}

Panser::~Panser()
{
    delete ui;
}

void Panser::getRecursos() {
    qDebug() << "Consiguiendo Recursos...";
    qDebug() << "HTML es Vacio?" << HTML_almacen.isEmpty();

    lista_CSS = new QStringList();

    QRegularExpression cssRegex("<link\\s+.*?href=\"(.*?)\".*?>");
    QRegularExpressionMatchIterator cssMatches = cssRegex.globalMatch(HTML_almacen);
    while(cssMatches.hasNext()) {
        qDebug() << "Adentro de CSS";
        QRegularExpressionMatch match = cssMatches.next();
        QString cssURL = match.captured(1);
        lista_CSS->push_back(cssURL);
    }

    qDebug() << "CSS obtenido";

    lista_JS = new QStringList();

    QRegularExpression jsRegex("<script\\s+.*?src=\"(.*?)\".*?>");
    QRegularExpressionMatchIterator jsMatches = jsRegex.globalMatch(HTML_almacen);
    while(jsMatches.hasNext()) {
        qDebug() << "Adentro de JS";
        QRegularExpressionMatch match = jsMatches.next();
        QString jsURL = match.captured(1);
        lista_JS->push_back(jsURL);
    }

    qDebug() << "JS obtenido";

    lista_img = new QStringList();

    QRegularExpression imgRegex("<img\\s+.*?src=\"(.*?)\".*?>");
    QRegularExpressionMatchIterator imgMatches = imgRegex.globalMatch(HTML_almacen);
    while(imgMatches.hasNext()) {
        qDebug() << "Adentro de IMG";
        QRegularExpressionMatch match = imgMatches.next();
        QString imgURL = match.captured(1);
        lista_img->push_back(imgURL);
    }

    qDebug() << "IMG obtenido";
    qDebug() << "Todos los Recursos Conseguidos...";
    qDebug() << "Todos los recursos obtenidos.";
    //QMessageBox::information(this, "Conseguido", "Todos los recursos obtenidos.");
}

void Panser::slot_descargar_HTML() {
    if (ui->leURL->text().isEmpty()) {
        QString dir = QFileDialog::getExistingDirectory(this, "Seleccionar Directorio", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (!dir.isEmpty()) {
            ruta_archivo = dir;
            qDebug() << "Directorio seleccionado para guardar archivos:" << ruta_archivo;
            ui->leURL->setText(ruta_archivo);
        } else {
            qDebug() << "No se seleccionó ningún directorio.";
            //QMessageBox::warning(this, "Error", "No se seleccionó ningún directorio.");
            return;
        }
    }

    if (!ui->leDireccion->text().isEmpty()) {
        qDebug() << "Descargando HTML...";

        ruta_archivo = ui->leURL->text();
        ruta_archivo += "/";
        qDebug() << "Direccion de Guardado:" << ruta_archivo;

        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_HTML_descargado(QNetworkReply*)));
        QNetworkRequest request(QUrl(ui->leDireccion->text()));
        manager->get(request);
    } else {
        qDebug() << "Falta la URL a analizar. Vuelva a Intentar";
        //QMessageBox::warning(this, "Error", "Falta la URL. Vuelve a intentar.");
    }
}

void Panser::slot_descargar_archivos() {
    getRecursos();

    qDebug() << "A punto de ponerme a descargar todos los Recursos...";
    // QMessageBox::information(this, "Iniciando", "Empezando la descarga de Recursos");

    pos_lista_CSS = 0;
    connect(this, SIGNAL(signal_iniciar_descarga_CSS()), this, SLOT(slot_descargar_CSS()));
    emit signal_iniciar_descarga_CSS();

    pos_lista_JS = 0;
    connect(this, SIGNAL(signal_iniciar_descarga_JS()), this, SLOT(slot_descargar_JS()));
    emit signal_iniciar_descarga_JS();

    pos_lista_img = 0;
    connect(this, SIGNAL(signal_iniciar_descarga_img()), this, SLOT(slot_descargar_IMG()));
    emit signal_iniciar_descarga_img();

    qDebug() << "Finalizado!";
    // QMessageBox::information(this, "Finalizado", "Descarga de archivos finalizada");
}

void Panser::slot_HTML_descargado(QNetworkReply* reply) {
    qDebug() << "Guardando HTML y Emitiendo SIGNAL...";
    HTML_almacen = reply->readAll();

    QString fileName = "/txt.html";
    QFile file(ruta_archivo + fileName);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Se ha creado el Archivo HTML";
        // QMessageBox::information(this, "Archivo HTML creado", "Se ha creado el Archivo " +fileName+ ".");
    }
    file.write(HTML_almacen.toUtf8());

    ui->teHTML->setText(HTML_almacen);
    emit signal_HTML_descargado();
}

void Panser::slot_descargar_CSS() {
    if (lista_CSS->isEmpty() || pos_lista_CSS == lista_CSS->size()) {
        if (archivos_CSS_descargados == lista_CSS->size()) {
            qDebug() << "Archivos CSS creados";
            // QMessageBox::information(this, "Archivos CSS creados", "Se han creado todos los archivos CSS.");
        }
        return;
    } else {
        manager = new QNetworkAccessManager();
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_CSS_descargado(QNetworkReply*)));

        qDebug() << "Descargando CSS... Estoy en la Posicion" << pos_lista_CSS << "| Size de Lista es:" << lista_CSS->size();
        qDebug() << "URL en la Posicion Actual:" << lista_CSS->at(pos_lista_CSS);
        QNetworkRequest request(QUrl(lista_CSS->at(pos_lista_CSS)));
        manager->get(request);
    }
}

void Panser::slot_descargar_JS() {
    if (lista_JS->isEmpty() || pos_lista_JS == lista_JS->size()) {
        if (archivos_JS_descargados == lista_JS->size()) {
            qDebug() << "Archivos JS creados";
            // QMessageBox::information(this, "Archivos JS creados", "Se han creado todos los archivos JS.");
        }
        return;
    } else {
        manager = new QNetworkAccessManager();
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_JS_descargado(QNetworkReply*)));

        qDebug() << "Descargando JS... Estoy en la Posicion" << pos_lista_JS << "| Size de Lista es:" << lista_JS->size();
        qDebug() << "URL en la Posicion Actual:" << lista_JS->at(pos_lista_JS);
        QNetworkRequest request(QUrl(lista_JS->at(pos_lista_JS)));
        manager->get(request);
    }
}

void Panser::slot_descargar_IMG() {
    if (lista_img->isEmpty() || pos_lista_img == lista_img->size()) {
        return;
    } else {
        manager = new QNetworkAccessManager();
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_img_descargado(QNetworkReply*)));

        qDebug() << "Descargando IMG... Estoy en la Posicion" << pos_lista_img << "| Size de Lista es:" << lista_img->size();
        qDebug() << "URL en la Posicion Actual:" << lista_img->at(pos_lista_img);
        QNetworkRequest request(QUrl(lista_img->at(pos_lista_img)));
        manager->get(request);

        connect(this, SIGNAL(signal_IMG_descargado()), this, SLOT(slot_descargar_IMG()));
        pos_lista_img++;
    }
}

void Panser::slot_CSS_descargado(QNetworkReply* reply) {
    qDebug() << "Descargando Archivo CSS y Guardando...";
    QString almacen_temporal = reply->readAll();

    QString fileName = QString::number(pos_lista_CSS);
    fileName += ".css";
    qDebug() << "Filename del CSS:" << fileName;

    QFile file(ruta_archivo + fileName);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "No se pudo crear un Archivo CSS con el Nombre" << fileName;
    }
    file.write(almacen_temporal.toUtf8());

    archivos_CSS_descargados++;
    pos_lista_CSS++;
    if (archivos_CSS_descargados == lista_CSS->size()) {
        qDebug() << "Archivos CSS creados";
        // QMessageBox::information(this, "Archivos CSS creados", "Se han descargado TODOS los archivos CSS.");
    }
    slot_descargar_CSS();
}

void Panser::slot_JS_descargado(QNetworkReply* reply) {
    qDebug() << "Descargando Archivo JS y Guardando...";
    QString almacen_temporal = reply->readAll();

    QString fileName = QString::number(pos_lista_JS);
    fileName += ".js";
    qDebug() << "Filename del JS:" << fileName;

    QFile file(ruta_archivo + fileName);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "No se pudo crear un Archivo JS con el Nombre" << fileName;
    }
    file.write(almacen_temporal.toUtf8());

    archivos_JS_descargados++;
    pos_lista_JS++;
    if (archivos_JS_descargados == lista_JS->size()) {
        qDebug() << "Archivos JS creados";
        // QMessageBox::information(this, "Archivos JS creados", "Se han descargado TODOS los archivos JS.");
    }
    slot_descargar_JS();
}

void Panser::slot_img_descargado(QNetworkReply* reply) {
    qDebug() << "Descargando Archivo IMG y Guardando...";
    QImage almacen_temporal = QImage::fromData(reply->readAll());

    QString fileName = QString::number(pos_lista_img);
    fileName += "img.png";
    qDebug() << "Filename de la IMG:" << fileName;

    QString fullFileName = ruta_archivo + fileName;
    QFile file(ruta_archivo + fileName);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Se ha creado un Archivo IMG con el Nombre" << fileName;
        // QMessageBox::information(this, "Imágen creada", "Se ha creado una imágen con el nombre " +fileName+ ".");
    }
    almacen_temporal.save(fullFileName);
    emit signal_IMG_descargado();
}

void Panser::slot_QDialog_img_disco() {
    QFileDialog dialog(this, "Abrir");
    dialog.setNameFilter("Imagen (*.png *.jpg)");
    connect(&dialog, SIGNAL(fileSelected(QString)), this, SLOT(slot_imagen_obtenida(QString)));
    dialog.exec();
}

void Panser::slot_imagen_obtenida(QString str) {
    QFile file(str);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "No se pudo abrir el Archivo";
        // QMessageBox::warning(this, "Apertura fallida", "Error.No se pudo abrir un archivo.");
        return;
    }

    QByteArray imageData = file.readAll();

    img.loadFromData(imageData);
    this->repaint();
}

void Panser::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if (!img.isNull()) {
        painter.drawImage(0, 0, img.scaled(this->size()));
    }
}
