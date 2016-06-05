#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pabackend.h"
#include "testcallback.h"

#include <QKeyEvent>
#include <QDebug>

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
    setFocusPolicy(Qt::StrongFocus);

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

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->isAutoRepeat() || e->modifiers()!= Qt::NoModifier) return;
    action_queue.push_back(Action {Action::KeyPress,e->key()});
    qDebug()<<action_queue[action_queue.size() - 1].key;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
    action_queue.push_back(Action {Action::KeyRelease, e->key()});
}

std::vector<Action> MainWindow::poll_input(){
    std::vector<Action> ret = std::vector<Action>(action_queue);
    action_queue.clear();
    return ret;
}
