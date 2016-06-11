#ifndef QSYNTH_IAUDIOEFFECT_H
#define QSYNTH_IAUDIOEFFECT_H

#include <QString>

namespace qSynth {

class IAudioEffect
{
public:
    virtual void process(float* samples,
                         unsigned long samplesCount) = 0;
    virtual QString name() const = 0;
};

} // namespace qSynth

#endif // QSYNTH_IAUDIOEFFECT_H
