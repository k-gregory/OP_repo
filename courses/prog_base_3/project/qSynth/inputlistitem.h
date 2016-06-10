#ifndef QSYNTH_INPUTLISTITEM_H
#define QSYNTH_INPUTLISTITEM_H

#include <QString>
#include <QDialog>
#include "igenericinput.h"

namespace qSynth {

class InputListItem
{
public:
    InputListItem(QString&& name,
                  IGenericInput* input,
                  QWidget* parent = nullptr,
                  QDialog* modificationDialog = nullptr
                  );
    void modify();
    const QString& getName() const;
    IGenericInput* getInput() const;
private:
    QString name;
    IGenericInput* input;
    QDialog* modificationDialog;
    QWidget* parent;
};

} // namespace qSynth

#endif // QSYNTH_INPUTLISTITEM_H
