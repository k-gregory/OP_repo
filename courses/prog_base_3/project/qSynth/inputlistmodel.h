#ifndef QSYNTH_INPUTLISTMODEL_H
#define QSYNTH_INPUTLISTMODEL_H

#include "igenericinput.h"
#include "inputlistitem.h"
#include <QDialog>
#include <QAbstractListModel>
#include <vector>

namespace qSynth {

class InputListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit InputListModel(QObject* parent);
    bool addInput(InputListItem& item);
    void modifyItem(const QModelIndex& idx);
    void removeItem(const QModelIndex& idx);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool insertRow(int row, const QModelIndex &parent);
    std::vector<GenericInputAction> getMultiplexedInput();
private:
    std::vector<InputListItem> inputs;
};

} // namespace qSynth

#endif // QSYNTH_INPUTLISTMODEL_H
