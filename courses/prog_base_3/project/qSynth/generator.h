#ifndef QSYNTH_GENERATOR_H
#define QSYNTH_GENERATOR_H

#include "iinputprocessor.h"
#include "iaudiocallback.h"
#include "iaudioeffect.h"
#include "spinlock.h"
#include <QObject>
#include <vector>

namespace qSynth {

class Generator : public QObject, public IAudioCallback
{
    Q_OBJECT
public:
    explicit Generator(IAudioEffect* effect, QObject* parent = nullptr);
    void processInput(const std::vector<GenericInputAction>& input) override;
    void fillBuffer(float* buffer, unsigned long frames) override;
    void addInputProcessor(IInputProcessor* p);
    void setEffect(IAudioEffect *value);

private:
    std::vector<IInputProcessor*> input_processors;
    IAudioEffect* effect;

    util::Spinlock input_lock;
    std::vector<GenericInputAction> danger_buffer;
    void dangerProcessInput();
signals:
    void framesGenerated(unsigned int count);

};

} // namespace qSynth

#endif // QSYNTH_GENERATOR_H
