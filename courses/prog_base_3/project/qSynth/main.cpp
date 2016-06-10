#include "mainwindow.h"
#include <QApplication>

#include "lib/midifile/MidiFile.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    MidiFile f;
    f.read("/tmp/a.mid");
    MidiEventList midi = f[11];
    cout<<midi.size()<<endl;
    for(int i = 0; i < midi.size();i++){
        MidiEvent ev = midi[i];
        if(!ev.isNoteOn()) continue;
        cout << ev.tick<<"\t|"<<(int)ev[1]<<endl;
    }

    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
}
