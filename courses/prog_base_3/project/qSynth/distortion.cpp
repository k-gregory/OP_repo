#include "distortion.h"
#include <algorithm>
#include <QInputDialog>

namespace qSynth {

QString Distortion::name() const{
    return "Distortion";
}

Distortion::Distortion(float limit, float coef)
    : limit(limit), coef(coef)
{

}

static inline float expDistort(float x){
    if(x > 0)
        return 1 - std::exp(-x);
    else
        return -1 + std::exp(x);
}

void Distortion::process(float *samples, unsigned long samplesCount){
    for(unsigned long i = 0; i < samplesCount; i++){
        samples[i] = expDistort(samples[i] * coef);
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

DistortionConfigurator::DistortionConfigurator(QWidget *parent)
    : parent(parent)
{

}

IAudioEffect* DistortionConfigurator::createNew(){
    float limit, coef;
    bool ok;
    limit = QInputDialog::getDouble(parent,"Distortion create","Limit:",1,0.001,1,5,&ok);
    if(!ok) return nullptr;
    coef = QInputDialog::getDouble(parent,"Distortion create","Coef:",1,0.001,30,5,&ok);
    if(!ok) return nullptr;

    return new Distortion(limit,coef);
}

bool DistortionConfigurator::configure(IAudioEffect *effect){
    float limit, coef;
    bool ok;

    Distortion* ef = dynamic_cast<Distortion*> (effect);
    if(ef == nullptr) return false;

    limit = QInputDialog::getDouble(parent,"Distortion create","Limit:",ef->limit,0.001,1,5,&ok);
    if(!ok) return false;
    coef = QInputDialog::getDouble(parent,"Distortion create","Coef:",ef->coef,0.001,30,5,&ok);
    if(!ok) return false;
    ef->limit = limit;
    ef->coef = coef;
    return true;
}

} // namespace qSynth

