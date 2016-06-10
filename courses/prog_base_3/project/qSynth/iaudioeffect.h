#ifndef QSYNTH_IAUDIOEFFECT_H
#define QSYNTH_IAUDIOEFFECT_H


namespace qSynth {

class IAudioEffect
{
public:
    virtual void process(float* samples,
                         unsigned long samplesCount) = 0;
};

} // namespace qSynth

#endif // QSYNTH_IAUDIOEFFECT_H
