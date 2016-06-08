#include "udpinputconfig.h"

namespace qSynth {

UDPInputConfig::UDPInputConfig(QWidget* pwgt, UDPInput* initial) :
    QDialog(pwgt),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    if(initial == nullptr) result = new UDPInput();
    else{
        result = initial;
        result->close();
    };
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(on_buttonBox_accepted()));
}

UDPInput* UDPInputConfig::getResult(){
    return result;
}

void UDPInputConfig::on_buttonBox_accepted()
{
    result->close();
    result->open(ui->spinBox->value());
}

} // namespace qSynth
