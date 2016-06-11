#ifndef QSYNTH_EFFECTTREEMODEL_H
#define QSYNTH_EFFECTTREEMODEL_H

#include "effecttreeitem.h"
#include <QAbstractItemModel>

namespace qSynth {

class EffectTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit EffectTreeModel(QObject* parent = 0);
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent) const override;
private:
    EffectTreeItem* root;
};

} // namespace qSynth

#endif // QSYNTH_EFFECTTREEMODEL_H
