#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iaudiobackend.h"
#include "generator.h"
#include "igenericinput.h"
#include "inputlistmodel.h"
#include "inputaddingdialog.h"
#include "effecttreemodel.h"
#include "ieffectconfigurator.h"
#include <QMainWindow>
#include <QHash>

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
    void setupInputCreator();
    void setupInputTimer();
    void setupIcons();
    void addKeyboardInput();
    void setupInputsModel();
    void setupEffectsModel();

    Ui::MainWindow *ui;
    InputAddingDialog* inputAddingDialog;
    qSynth::IAudioBackend* audio;
    qSynth::Generator* cb;
    bool playing = false;

    qSynth::InputListModel* inputListModel = nullptr;
    qSynth::EffectTreeModel* effectTreeModel = nullptr;
    QHash<QString, qSynth::IEffectConfigurator*> effectC;
    QTimer* input_timer;
private slots:
    void feedInput();
    void on_inputModifyBtn_clicked();
    void on_inputAddBtn_clicked();
    void on_addEffectBtn_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
