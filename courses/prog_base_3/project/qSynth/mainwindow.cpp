#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pabackend.h"
#include "testcallback.h"

using namespace qSynth;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cb = new TestCallback();
    audio = new PABackend(cb);
}

MainWindow::~MainWindow()
{
    delete ui;
}
