#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pabackend.h"
#include "testcallback.h"

using namespace qSynth;

void MainWindow::setupIcons(){
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupIcons();

    cb = new TestCallback();
    audio = new PABackend(cb);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    playing = !playing;
    QStyle::StandardPixmap newIcon = playing ? QStyle::SP_MediaPause : QStyle::SP_MediaPlay;
    ui->playButton->setIcon(style()->standardIcon(newIcon));
    ui->playButton->setText(playing ? "Pause" : "Play");
    audio->togglePause();
}
