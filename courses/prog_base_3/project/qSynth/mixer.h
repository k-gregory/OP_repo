#ifndef QSYNTH_MIXER_H
#define QSYNTH_MIXER_H

#include "iaudioeffect.h"
#include <vector>

namespace qSynth {

class Mixer : public IAudioEffect
{
public:
    Mixer();
    ~Mixer();
    std::vector<IAudioEffect*> effects;
    std::vector<float> coefs;
    QString name() const override;
    void process(float* samples, unsigned long frames) override;
    void removeEffect(unsigned int index);
    void insertEffect(unsigned int index, IAudioEffect* effect);
private:
    std::size_t tmp_buff_size = 4096;
    float* tmp_buff = new float[tmp_buff_size];
};

} // namespace qSynth

#endif // QSYNTH_MIXER_H
