#ifndef QSYNTH_MIXERCONFIGURATOR_H
#define QSYNTH_MIXERCONFIGURATOR_H

#include "ieffectconfigurator.h"
#include <QWidget>

namespace qSynth {

class MixerConfigurator : public IEffectConfigurator
{
public:
    explicit MixerConfigurator(QWidget* p);
    IAudioEffect* createNew() override;
    bool configure(IAudioEffect *effect) override;
private:
    QWidget* parent;
};

} // namespace qSynth

#endif // QSYNTH_MIXERCONFIGURATOR_H
