#include "distortion.h"
#include <algorithm>

namespace qSynth {

QString Distortion::name() const{
    return "Distortion";
}

Distortion::Distortion(float limit, float coef)
    : limit(limit), coef(coef)
{

}

void Distortion::process(float *samples, unsigned long samplesCount){
    for(unsigned long i = 0; i < samplesCount; i++){
        samples[i]*= coef;
        samples[i] = std::min(samples[i], coef);
        samples[i] = std::max(samples[i], -coef);
    }
}

float Distortion::getCoef() const
{
    return coef;
}

void Distortion::setCoef(float value)
{
    coef = value;
}

float Distortion::getLimit() const
{
    return limit;
}

void Distortion::setLimit(float value)
{
    limit = value;
}

} // namespace qSynth

