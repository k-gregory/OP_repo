#include "inputaddingdialog.h"
#include "ui_inputaddingdialog.h"
#include <QDebug>

InputAddingDialog::InputAddingDialog(const QSet<IInputCreator *> &inputCreators, QWidget *parent)
    :QDialog(parent),ui(new Ui::InputAddingDialog)
{
    ui->setupUi(this);

    for(IInputCreator* ic : inputCreators){
        ui->intemSelectionBox->addItem(ic->creatorName());
        this->inputCreators.insert(ic->creatorName(), ic);
    }
}

qSynth::InputListItem* InputAddingDialog::getInput(QString&& name){
    newName = name;
    if(this->exec() == Accepted){
        return ret;
    } else return nullptr;
}

InputAddingDialog::~InputAddingDialog()
{
    delete ui;
}

void InputAddingDialog::on_intemSelectionBox_activated(const QString &)
{

}

void InputAddingDialog::on_buttonBox_accepted()
{
    auto it = inputCreators.find(ui->intemSelectionBox->currentText());
    if(it!=inputCreators.end()){
        ret = it.value()->createInput(std::move(newName));
        accept();
    }
}
