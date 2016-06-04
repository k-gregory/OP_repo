#include "mainwindow.h"
#include <QApplication>

#include "testcallback.h"
#include "pabackend.h"

using namespace qSynth;

int main(int argc, char *argv[])
{
    IAudioCallback* cb = new TestCallback();
    IAudioBackend* b = new PABackend(cb);
    b->start();
    Pa_Sleep(100000);
    b->stop();
    delete cb;
    delete b;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
