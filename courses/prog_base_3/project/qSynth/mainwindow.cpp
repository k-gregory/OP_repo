#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "simplegenerator.h"
#include "pabackend.h"

#include <QTimer>
#include <QVBoxLayout>
#include <QStandardItemModel>

#include "inputlistmodel.h"
#include "udpinputcreator.h"
#include "midiinputcreator.h"

#include "noparamsconfigurator.h"
#include "distortion.h"
#include "effectsequence.h"
#include "mixerconfigurator.h"
#include "keyreadinputcreator.h"

#include <QDebug>

using namespace qSynth;

void MainWindow::setupInputCreator(){
    QSet<IInputCreator*> inputCreators;
    inputCreators.insert(new UDPInputCreator(this));
    inputCreators.insert(new MidiInputCreator(cb));
    inputCreators.insert(new KeyReadInputCreator(krw));
    inputAddingDialog = new InputAddingDialog(inputCreators, this);
}

void MainWindow::addKeyboardInput(){
    QVBoxLayout* vbox = new QVBoxLayout;
    krw = new KeyboardReaderWidget;

    vbox->addWidget(krw);
    ui->keyboardInputGB->setLayout(vbox);     
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
    inputListModel = new InputListModel(this);
    ui->inputsList->setModel(inputListModel);
}

void MainWindow::setupEffectsModel(){
    effectC.insert("Guitar", new GuitarCreator(this, cb));
    effectC.insert("Distortion", new DistortionConfigurator(this));
    effectC.insert("Sequence", new NoParamsConfigurator<EffectSequence>);
    effectC.insert("Mixer", new MixerConfigurator(this));

    for(auto e: effectC.keys())
        ui->effectCb->addItem(e);
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

    effectTreeModel = new EffectTreeModel(this);
    ui->effectsTree->setModel(effectTreeModel);
    cb = new Generator(effectTreeModel->getRootEffect());

    setupInputsModel();
    setupEffectsModel();

    addKeyboardInput();
    setupInputCreator();

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

void MainWindow::on_inputModifyBtn_clicked()
{
    QModelIndex sel = ui->inputsList->selectionModel()->currentIndex();
    inputListModel->modifyItem(sel);
}

void MainWindow::on_inputAddBtn_clicked()
{
    if(ui->newInputNameEdit->text().isEmpty()) return;
    qSynth::InputListItem* new_in = inputAddingDialog->getInput(ui->newInputNameEdit->text());
    if(new_in != nullptr) inputListModel->addInput(*new_in);
}

void MainWindow::on_addEffectBtn_clicked()
{
    IAudioEffect* e = effectC.value(ui->effectCb->currentText())->createNew();
    if(!e) return;
    QModelIndex sel = ui->effectsTree->selectionModel()->currentIndex();
    effectTreeModel->addEffect(e,sel);
}

void MainWindow::on_pushButton_clicked()
{
    QModelIndex idx = ui->effectsTree->selectionModel()->currentIndex();
    if(!idx.isValid()) return;
    EffectTreeItem* i = effectTreeModel->getItem(idx);
    if(!i) return;
    effectC.value(i->effect->name())->configure(i->effect);
}

void MainWindow::on_inputDelBtn_clicked()
{
    QModelIndex sel = ui->inputsList->selectionModel()->currentIndex();
    inputListModel->removeItem(sel);
}

void MainWindow::on_effectDelBtn_clicked()
{
    QModelIndex idx = ui->effectsTree->selectionModel()->currentIndex();
    effectTreeModel->removeEffect(idx);
}
