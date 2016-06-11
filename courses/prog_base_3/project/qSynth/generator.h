#ifndef QSYNTH_GENERATOR_H
#define QSYNTH_GENERATOR_H

#include "iaudiocallback.h"
#include "spinlock.h"
#include <QObject>

namespace qSynth {

class Generator : public QObject, public IAudioCallback
{
    Q_OBJECT
public:
    explicit Generator(QObject* parent = nullptr);
    void processInput(const std::vector<GenericInputAction>& input) override;
    void fillBuffer(float* buffer, unsigned long frames) override;
private:
    util::Spinlock input_lock;
    std::vector<GenericInputAction> danger_buffer;
    void dangerProcessInput();
signals:
    void framesGenerated(unsigned int count);

};

} // namespace qSynth

#endif // QSYNTH_GENERATOR_H
