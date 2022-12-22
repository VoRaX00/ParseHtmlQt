#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList getData(QString text){
    QStringList list;
    QRegExp regex1("(<span title=\"ощущается как -24°\" class=\"weather__temp svelte-xn9nd0\" data-testid=\"weather-temp\">)(.[0-9]+)(°</span>)");
    QRegExp regex2("(<div class=\"rate__currency svelte-ov6yem\">)([\\d.]+)(</div>)");
    int lastPos = 0;
    regex1.indexIn(text);
    list.append(regex1.cap(2));
    while((lastPos = regex2.indexIn(text,lastPos)) != -1){
        list.append(regex2.cap(2));
        lastPos +=regex2.matchedLength();
    }

    return list;
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        //QByteArray b = file.readAll();
        QString text=file.readAll();
        QStringList data = getData(text);
        ui->tLineEdit->setText(data[0]);
        ui->eurLineEdit->setText(data[1]);
        ui->usdLineEdit->setText(data[2]);
    }
}

