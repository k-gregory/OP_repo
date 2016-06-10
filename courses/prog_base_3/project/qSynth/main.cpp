#include "mainwindow.h"
#include <QApplication>

#include "lib/midifile/MidiFile.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{

    /*
    MidiFile f;
    f.read("/tmp/imb.mid");
    int c = 0;
    MidiEventList midi = f[1];
    for(int i = 0; i < midi.size()-1;i++){
        MidiEvent ev = midi[i];
        if(!ev.isNoteOn()) continue;
        cout << ev.tick/1000.f<<"\t|"<<(int)ev[1]<<endl;
        c++;
    }
    cout<<c-f[1].size()<<endl;*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
