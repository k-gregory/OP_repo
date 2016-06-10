#ifndef INPUTADDINGDIALOG_H
#define INPUTADDINGDIALOG_H

#include <QDialog>
#include <QHash>
#include <QString>
#include "iinputcreator.h"

namespace Ui {
class InputAddingDialog;
}

class InputAddingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InputAddingDialog(const QSet<IInputCreator*>& inputCreators,
                               QWidget *parent = 0);
    ~InputAddingDialog();
    qSynth::InputListItem* getInput(QString&& name);

private slots:
    void on_intemSelectionBox_activated(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::InputAddingDialog *ui;
    QHash<QString,IInputCreator*> inputCreators;
    qSynth::InputListItem* ret;
    QString newName;
};

#endif // INPUTADDINGDIALOG_H
