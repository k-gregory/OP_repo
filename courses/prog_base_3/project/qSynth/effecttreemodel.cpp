#include "effecttreemodel.h"
#include "mixer.h"
#include "effectsequence.h"
#include "guitargenerator.h"
#include "distortion.h"

#include <QDebug>

namespace qSynth {

EffectTreeModel::EffectTreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    root = new EffectTreeItem(EffectTreeItem::Mixer,new Mixer);
    /*EffectTreeItem* seq_it = new EffectTreeItem(EffectTreeItem::Sequence,
                                                new EffectSequence,
                                                root);
    root->insertChild(0, seq_it);
    EffectTreeItem* dist_it = new EffectTreeItem(EffectTreeItem::Other,
                                                 new Distortion,
                                                 seq_it);
    seq_it->insertChild(0, dist_it);*/
}

int EffectTreeModel::columnCount(const QModelIndex&) const{
    return 1;
}

QVariant EffectTreeModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || role != Qt::DisplayRole) return QVariant();
    EffectTreeItem* it = static_cast<EffectTreeItem*>(index.internalPointer());
    return it->effect->name();
}

QModelIndex EffectTreeModel::index(int row, int column, const QModelIndex &parent) const{
    if(!hasIndex(row, column, parent)) return QModelIndex();
    EffectTreeItem* parentItem;
    if(!parent.isValid())
        parentItem = root;
    else
       parentItem = static_cast<EffectTreeItem*>(parent.internalPointer());

    EffectTreeItem* childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row,column,childItem);
    else return QModelIndex();


}

QModelIndex EffectTreeModel::parent(const QModelIndex &index) const{
    if(!index.isValid()) return QModelIndex();
    EffectTreeItem* parentItem =
            static_cast<EffectTreeItem*>(index.internalPointer())->parent;
    if(parentItem == root) return QModelIndex();
    else return createIndex(parentItem->row(), 0, parentItem);
}

int EffectTreeModel::rowCount(const QModelIndex &parent) const{
    EffectTreeItem* it;
    if(!parent.isValid())
        it = root;
    else it = static_cast<EffectTreeItem*>(parent.internalPointer());
    return it->children.size();
}

} // namespace qSynth

