#include "guitarcreator.h"
#include <QInputDialog>
#include "guitargenerator.h"
#include "guitarinputprocessor.h"

GuitarCreator::GuitarCreator(QWidget* parent, qSynth::Generator* gen)
    : parent(parent), g(gen)

{

}

qSynth::IAudioEffect* GuitarCreator::createNew(){
   bool ok;
   QString res;
   res  = QInputDialog::getText(parent, "Guitar creation","Input name",QLineEdit::Normal,"KeyRead Widget",&ok);
   if(!ok) return nullptr;
   qSynth::guitar::GuitarGenerator* ret = new qSynth::guitar::GuitarGenerator();
   g->addInputProcessor(new qSynth::GuitarInputProcessor(res,ret));
   return ret;
}

bool GuitarCreator::configure(qSynth::IAudioEffect *effect){
    return false;
}

