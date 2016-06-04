#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iaudiobackend.h"
#include "iaudiocallback.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_playButton_clicked();

    void on_pauseButton_clicked();

private:
    Ui::MainWindow *ui;
    qSynth::IAudioBackend* audio;
    qSynth::IAudioCallback* cb;
};

#endif // MAINWINDOW_H
