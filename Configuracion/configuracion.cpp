#include "configuracion.h"
#include "ui_configuracion.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QDir>

Configuracion::Configuracion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Configuracion)
{
    ui->setupUi(this);
}

Configuracion::~Configuracion()
{
    delete ui;
}

void Configuracion::on_btnGuardar_clicked()
{
    // Obtener la informacion del GUI
    QString direccion = ui->inDireccion->text();
    int puerto = ui->inPuerto->value();
    bool caja1 = ui->chkCaja1->isChecked();
    bool caja2 = ui->chkCaja2->isChecked();
    bool caja3 = ui->chkCaja3->isChecked();
    bool caja4 = ui->chkCaja4->isChecked();

    // Verificamos si la informacion recopilada es correcta
    //qDebug() << direccion << puerto << caja1 << caja2 << caja3 << caja4;

    // Establecer un nombre de archivo tempral en el directorio "home" del usuario
    QString temporal =QDir::home().absolutePath()+"/sin_titulo.cfg";
    qDebug() << temporal;


    //Abrir cuadro de dialogo para colocar el nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this, "Guardar configuracion",
                                                   temporal,"Archivo de configuracion(*.cfg)");
    // Crear el objeto QFile
    QFile archivo(nombreArchivo);

    //Verificar si se puede escribir sobre el archivo
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Crear el objettoQTextString
            QTextStream out(&archivo);
            // Escribiendo datos en el
          out <<"Servidor ="<< direccion << endl;
          out <<"Puerto = "<< puerto << endl;
          out <<"Caja 1 = "<< caja1 << endl;
          out <<"Caja 2 = "<< caja2 << endl;
          out <<"Caja 3 = "<< caja3 << endl;
          out <<"Caja 4 = "<< caja4 << endl;
          qDebug() << "Archivo almecenado en:" << nombreArchivo;
          // Cerrar archivo
            archivo.close();
            QMessageBox guardado;
            guardado.setText("Archivo guardado correctamente");
            guardado.exec();
        }
}

void Configuracion::on_btnAbrir_clicked()
{
    QString nombre = QFileDialog::getOpenFileName(this, "Abrir configuracion",
                                                      "C:/Users/ACER ASPIRE3", "config(*.cfg)");
        QFile file(nombre);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QStringList datos;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString linea = in.readLine();
            datos << linea;
        }
        QStringList data = datos[0].split("=");
        QStringList data1 = datos[1].split("=");
        QStringList data2 = datos[2].split("=");
        QStringList data3 = datos[3].split("=");
        QStringList data4 = datos[4].split("=");
        QStringList data5 = datos[5].split("=");

        ui->inDireccion->setText(data[1]);
        ui->inPuerto->setValue(data1[1].toInt());
        ui->chkCaja1->setChecked(data2[1].toInt());
        ui->chkCaja2->setChecked(data3[1].toInt());
        ui->chkCaja3->setChecked(data4[1].toInt());
        ui->chkCaja4->setChecked(data5[1].toInt());


        file.close();
}
