#ifndef QSYNTH_DISTORTION_H
#define QSYNTH_DISTORTION_H

#include "iaudioeffect.h"

namespace qSynth {

class Distortion : public IAudioEffect
{
public:
    Distortion(float limit = 1, float coef = 1);
    void process(float* samples, unsigned long samplesCount) override;

    float getCoef() const;
    void setCoef(float value);

    float getLimit() const;
    void setLimit(float value);

private:
    float limit;
    float coef;
};

} // namespace qSynth

#endif // QSYNTH_DISTORTION_H
