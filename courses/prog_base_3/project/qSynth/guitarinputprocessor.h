#ifndef QSYNTH_GUITARINPUTPROCESSOR_H
#define QSYNTH_GUITARINPUTPROCESSOR_H

#include "iinputprocessor.h"
#include "guitargenerator.h"

namespace qSynth {

class GuitarInputProcessor : public IInputProcessor
{
public:
    void process(std::vector<GenericInputAction> input) override;
    GuitarInputProcessor(QString acceptName, guitar::GuitarGenerator* g);
private:
    guitar::GuitarGenerator* guitar;
    QString acceptName;
};

} // namespace qSynth

#endif // QSYNTH_GUITARINPUTPROCESSOR_H
