#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iaudiobackend.h"
#include "iaudiocallback.h"
#include "igenericinput.h"
#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public qSynth::IGenericInput
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    std::vector<qSynth::Action> poll_input() override;
    ~MainWindow();

private slots:
    void on_playButton_clicked();

private:
    void setupIcons();

    Ui::MainWindow *ui;
    qSynth::IAudioBackend* audio;
    qSynth::IAudioCallback* cb;
    bool playing = false;

    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    std::vector<qSynth::Action> action_queue;
};

#endif // MAINWINDOW_H
