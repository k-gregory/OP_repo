#include "mixerconfigurator.h"
#include "mixer.h"
#include <QInputDialog>

namespace qSynth {

MixerConfigurator::MixerConfigurator(QWidget* p)
    : parent(p)
{

}

IAudioEffect* MixerConfigurator::createNew(){
    return new Mixer();
}

bool MixerConfigurator::configure(IAudioEffect *effect){
    bool ok;
    Mixer* m = dynamic_cast<Mixer*>(effect);
    if(m == nullptr) return false;
    for(unsigned int i = 0;i  < m->effects.size();i++){
        QString q = QString("Set level of %1").arg(i+1);
        float newValue = QInputDialog::getDouble(parent,"Mixer config",q,m->coefs[i],0.001,100,4,&ok);
        if(!ok) return false;
        m->coefs[i] = newValue;
    }
    return true;
}

} // namespace qSynth

