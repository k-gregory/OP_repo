#include "guitarinputprocessor.h"
#include <QDebug>

namespace qSynth {

GuitarInputProcessor::GuitarInputProcessor(QString acceptName, guitar::GuitarGenerator* g)
    : guitar(g) , acceptName(acceptName)
{

}

static float freqFromMidiKey(char key){
    constexpr float coef = log(2)/12.f;
    return std::exp((key - 69) * coef)*440;
}

void GuitarInputProcessor::process(std::vector<GenericInputAction> input){
    for(GenericInputAction& a : input){
        qDebug()<<"lel";
        if(a.inputName != acceptName)
            continue;
        if(a.type == GenericInputAction::KeyPress)
            guitar->playFree(freqFromMidiKey(a.key));
    }
}

} // namespace qSynth

