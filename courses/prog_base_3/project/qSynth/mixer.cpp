#include "mixer.h"
#include <algorithm>

namespace qSynth {

QString Mixer::name() const{
    return "Mixer";
}

Mixer::Mixer()
{
}

void Mixer::process(float *samples, unsigned long frames){
    if(tmp_buff_size < frames){
        delete[] tmp_buff;
        tmp_buff = new float[frames * 2];
        tmp_buff_size = frames * 2;
    }
    std::fill(samples, samples+frames,0);

    for(std::size_t i = 0; i < effects.size(); i++){
        effects[i]->process(tmp_buff, frames);
        for(std::size_t j = 0; j  <frames; j++)
            samples[j] += tmp_buff[j] * coefs[j];
    }
}

void Mixer::removeEffect(unsigned int index){
    if(index >= effects.size()) return;
    effects.erase(effects.begin() + index);
    coefs.erase(coefs.begin() + index);
}

void Mixer::insertEffect(unsigned int index, IAudioEffect *effect){
    if(index > effects.size()) return;
    effects.insert(effects.begin() + index, effect);
    coefs.insert(coefs.begin(), 1);
}

Mixer::~Mixer(){
    delete[] tmp_buff;
}

} // namespace qSynth

