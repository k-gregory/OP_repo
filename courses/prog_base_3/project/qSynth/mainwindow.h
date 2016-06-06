#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iaudiobackend.h"
#include "iaudiocallback.h"
#include "igenericinput.h"
#include <QMainWindow>
#include <unordered_set>

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

private:
    void setupInputTimer();
    void setupIcons();
    void addKeyboardInput();
    void setupInputsModel();

    Ui::MainWindow *ui;
    qSynth::IAudioBackend* audio;
    qSynth::IAudioCallback* cb;
    bool playing = false;

    std::unordered_set<qSynth::IGenericInput*> inputs;
    QTimer* input_timer;
private slots:
    void feedInput();
};

#endif // MAINWINDOW_H
