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

    void addEffect(IAudioEffect* e, QModelIndex& idx);
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent) const override;

    bool insertRow(int row, const QModelIndex &parent);
private:
    EffectTreeItem* getItem(const QModelIndex& idx) const;
    EffectTreeItem* root;
};

} // namespace qSynth

#endif // QSYNTH_EFFECTTREEMODEL_H
