#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sock = new QUdpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sock;
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->isAutoRepeat() || e->type()!= QKeyEvent::KeyPress) return;
    qint32 array[12];
    array[0] = 0;
    array[1] = e->key();
    array[2] = e->modifiers();
    array[3] = e->text()[0].toLatin1();
    for(int i = 4; i < 12; i++){
        array[i] = 0;
    }

    qDebug()<<sock->writeDatagram((char*)array,
                                  sizeof(qint32)*12,
                                  QHostAddress(ui->ipEdit->text()),
                                  8000);
}
