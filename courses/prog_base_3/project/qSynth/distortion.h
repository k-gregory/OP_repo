#ifndef QSYNTH_DISTORTION_H
#define QSYNTH_DISTORTION_H

#include "iaudioeffect.h"
#include "ieffectconfigurator.h"
#include <QWidget>

namespace qSynth {

class DistortionConfigurator;

class Distortion : public IAudioEffect
{
public:
    Distortion(float limit = 1, float coef = 1);
    QString name() const override;
    void process(float* samples, unsigned long samplesCount) override;

    float getCoef() const;
    void setCoef(float value);

    float getLimit() const;
    void setLimit(float value);

private:
    float limit;
    float coef;
    friend class DistortionConfigurator;
};

class DistortionConfigurator : public IEffectConfigurator{
public:
    DistortionConfigurator(QWidget* parent);
    IAudioEffect* createNew() override;
    bool configure(IAudioEffect *effect) override;
private:
    QWidget* parent;
};

} // namespace qSynth

#endif // QSYNTH_DISTORTION_H
