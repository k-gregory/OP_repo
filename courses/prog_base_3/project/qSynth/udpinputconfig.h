#ifndef QSYNTH_UDPINPUTCONFIG_H
#define QSYNTH_UDPINPUTCONFIG_H

#include "ui_udpinputconfig.h"
#include "udpinput.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

namespace qSynth {

class UDPInputConfig : public QDialog
{
    Q_OBJECT
public:
    UDPInputConfig(QWidget* pwgt = nullptr, UDPInput* initial = nullptr);
    UDPInput* getResult();
private slots:
    void on_buttonBox_accepted();

private:
    UDPInput* result;
    Ui::Dialog* ui;
};

} // namespace qSynth

#endif // QSYNTH_UDPINPUTCONFIG_H
