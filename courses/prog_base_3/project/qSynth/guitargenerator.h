#ifndef QSYNTH_GUITAR_GUITARGENERATOR_H
#define QSYNTH_GUITAR_GUITARGENERATOR_H

#include "constants.h"

#include "iaudioeffect.h"
#include <cmath>

namespace qSynth {
namespace guitar {

class GuitarGenerator :  IAudioEffect
{
    static constexpr auto string_count = 6;
    static constexpr auto string_max_swing_time = 5;
    static constexpr unsigned long swing_last_pos = string_max_swing_time * SAMPLE_RATE;
    static constexpr float sample_time = 1.f/SAMPLE_RATE;
    static constexpr unsigned int harmAmplitudesCount = 10;
    static constexpr float PI = 3.14159265359;

    struct StringInfo{
        unsigned int base_freq;
        unsigned long samples_played;
        bool active;
    };

    /*
     * Amplitudes taken from
     * https://blog.amartynov.ru/fft-анализ-и-аддитивный-синтез-гитары
     */
    struct AmplitudeModel{
        float A;
        float B;
        float C;
        float D;

        inline float calc(float time){
            return (A*time*time+B*time+C)*std::exp(D*time);
        }
    };
    AmplitudeModel harmAmplitudesInfo[harmAmplitudesCount] = {
        {0.0000079585,-0.3510846478,6454.3454366928,-0.0000516264},
        {0.0000206901,-0.3488352257,8078.2537944248,-0.0000744984},
        {0.0000020941,-0.0740199361,5368.4675414570,-0.0000562070},
        {0.0000004000,-0.0047107807,1941.7439223206,-0.0000572963},
        {0.0000001352,-0.0198556689,752.7893216837,-0.0000356882},
        {0.0000000249,-0.0035589589,122.7479688853,-0.0000300193},
        {0.0000003983,-0.0103417997,147.9820209126,-0.0001183942},
        {0.0000371598,-0.4954659848,1892.8311983538,-0.0003420994},
        {0.0000081147,-0.1803345539,1197.5593762439,-0.0001971705},
        {0.0000000241,-0.0020081514,46.9338124257,-0.0000536678}
    };
public:
    GuitarGenerator();
    ~GuitarGenerator();
    void process(const float *samples_in, float *samples_out, unsigned long samplesCount) override;
    void setStringFrequency(unsigned int string, unsigned int freq);
    void playString(unsigned int string, unsigned int freq);
    void playString(unsigned int string);
private:
    void initStrings();
    void precalculateAmplitudes();

    using arrType = float(*)[harmAmplitudesCount];
    arrType harmAmplitudes = new float[swing_last_pos+SAMPLE_RATE][harmAmplitudesCount];
    StringInfo strings[string_count];
};

} // namespace guitar
} // namespace qSynth

#endif // QSYNTH_GUITAR_GUITARGENERATOR_H
