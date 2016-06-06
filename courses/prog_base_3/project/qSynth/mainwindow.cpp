#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "simplegenerator.h"
#include "pabackend.h"
#include "keyboardreaderwidget.h"

#include <QTimer>
#include <QVBoxLayout>
#include <QStandardItemModel>

#include <QDebug>

using namespace qSynth;


void MainWindow::addKeyboardInput(){
    QVBoxLayout* vbox = new QVBoxLayout;
    KeyboardReaderWidget* krw = new KeyboardReaderWidget;
    vbox->addWidget(krw);
    ui->keyboardInputGB->setLayout(vbox);
    inputs.insert(krw);
}

void MainWindow::setupInputTimer(){
    input_timer = new QTimer(this);
    connect(input_timer,SIGNAL(timeout()),this,SLOT(feedInput()));
    input_timer->start(1);
}

void MainWindow::feedInput(){
    std::vector<GenericInputAction> multiplexed;
    for(IGenericInput* in: inputs){
        if(!in->hasInput()) continue;
        std::vector<GenericInputAction> current_in = in->pollInput();
        multiplexed.insert(multiplexed.end(), current_in.begin(), current_in.end());
    }
    if(multiplexed.size() > 0 && playing)
        cb->processInput(multiplexed);
}

void MainWindow::setupInputsModel(){
    QStandardItemModel * m = new QStandardItemModel(1,1);
    QModelIndex idx = m->index(0,0);
    for(int i = 0; i < 5;i++){
        m->insertRow(i,idx);
    }

    QStandardItemModel* model = new QStandardItemModel(5,3);

    for(int nTopRow = 0; nTopRow < 5; nTopRow++){
        QModelIndex index = model->index(nTopRow, 0);
        model->setData(index, "item" + QString::number(nTopRow + 1));

        model->insertRows(0, 4, index);
        model->insertColumns(0, 3, index);
        for(int nRow = 0; nRow < 4; nRow++)
            for(int nCol = 0; nCol < 3; nCol++){
                QString strPos = QString("%1,%2").arg(nRow).arg(nCol);
                model->setData(model->index(nRow,nCol, index), strPos);
            }
    }

    ui->effectsTree->setModel(model);
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
    addKeyboardInput();
    setupInputsModel();

    cb = new SimpleGenerator();
    audio = new PABackend(cb);

    setupInputTimer();//After generator created
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
