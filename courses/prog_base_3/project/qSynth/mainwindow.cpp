#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "simplegenerator.h"
#include "pabackend.h"
#include "keyboardreaderwidget.h"

#include <QTimer>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include "inputlistmodel.h"

#include <QDebug>

using namespace qSynth;


void MainWindow::addKeyboardInput(){
    QVBoxLayout* vbox = new QVBoxLayout;
    KeyboardReaderWidget* krw = new KeyboardReaderWidget;
    vbox->addWidget(krw);
    ui->keyboardInputGB->setLayout(vbox);
    inputListModel->addInput(krw,"KeyRead widget");
}

void MainWindow::setupInputTimer(){
    input_timer = new QTimer(this);
    connect(input_timer,SIGNAL(timeout()),this,SLOT(feedInput()));
    input_timer->start(1);
}

void MainWindow::feedInput(){
    std::vector<GenericInputAction> multiplexed =
            inputListModel->getMultiplexedInput();
    if(multiplexed.size() > 0 && playing)
        cb->processInput(multiplexed);
}

void MainWindow::setupInputsModel(){
    inputListModel = new InputListModel;
    ui->inputsList->setModel(inputListModel);
}

void MainWindow::setupIcons(){
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupIcons();
    setupInputsModel();
    addKeyboardInput();

    cb = new SimpleGenerator();
    audio = new PABackend(cb);

    setupInputTimer();//After generator created
}

MainWindow::~MainWindow()
{
    delete ui;
    delete inputListModel;
}

void MainWindow::on_playButton_clicked()
{
    playing = !playing;
    QStyle::StandardPixmap newIcon = playing ? QStyle::SP_MediaPause : QStyle::SP_MediaPlay;
    ui->playButton->setIcon(style()->standardIcon(newIcon));
    ui->playButton->setText(playing ? "Pause" : "Play");
    audio->togglePause();
}
