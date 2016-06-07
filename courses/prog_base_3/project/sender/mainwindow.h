#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* e);

private slots:
    void on_ipEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    QUdpSocket* sock;
    QHostAddress addr;
    int port;
};

#endif // MAINWINDOW_H
