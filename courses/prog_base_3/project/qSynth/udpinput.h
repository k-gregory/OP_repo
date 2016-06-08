#ifndef QSYNTH_UDPINPUT_H
#define QSYNTH_UDPINPUT_H

#include "igenericinput.h"
#include <QUdpSocket>

namespace qSynth {

class UDPInput : public QObject, public IGenericInput
{
    Q_OBJECT
public:
    explicit UDPInput(QObject* parent = nullptr);
    ~UDPInput();
    std::vector<GenericInputAction> pollInput() override;
    bool hasInput() override;
    void close();
    bool open(int port);
    quint16 getPort();

private slots:
    void readDatagrams();

private:
    QUdpSocket* sock = nullptr;
    bool listening = false;
    std::vector<GenericInputAction> input_queue;
};

} // namespace qSynth

#endif // QSYNTH_UDPINPUT_H
