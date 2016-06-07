#ifndef QSYNTH_INPUTLISTMODEL_H
#define QSYNTH_INPUTLISTMODEL_H

#include "igenericinput.h"
#include <QDialog>
#include <QAbstractListModel>
#include <vector>

namespace qSynth {

class InputListModel : public QAbstractListModel
{
    struct InputInfo{
        IGenericInput* i;
        QString name;
        QDialog* modificationDialog = nullptr;
    };

public:
    InputListModel();
    bool addInput(IGenericInput* i, QString name);
    void modifyItem(const QModelIndex& idx);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool insertRow(int row, const QModelIndex &parent);
    std::vector<GenericInputAction> getMultiplexedInput();
private:
    std::vector<InputInfo> inputs;
};

} // namespace qSynth

#endif // QSYNTH_INPUTLISTMODEL_H
