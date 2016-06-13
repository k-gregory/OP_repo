#include "mainwindow.h"
#include <QApplication>

#include "lib/midifile/MidiFile.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
