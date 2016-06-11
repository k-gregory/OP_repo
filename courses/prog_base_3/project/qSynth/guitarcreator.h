#ifndef GUITARCREATOR_H
#define GUITARCREATOR_H

#include "ieffectconfigurator.h"
#include <QWidget>
#include "generator.h"

class GuitarCreator : public qSynth::IEffectConfigurator
{
public:
    GuitarCreator(QWidget* p,qSynth::Generator* gen);
    qSynth::IAudioEffect* createNew() override;
    bool configure(qSynth::IAudioEffect *effect) override;
private:
    QWidget* parent;
    qSynth::Generator* g;
};

#endif // GUITARCREATOR_H
