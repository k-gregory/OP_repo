#include "effecttreemodel.h"
#include "mixer.h"
#include "effectsequence.h"
#include "guitargenerator.h"
#include "distortion.h"
#include "mixer.h"
#include "effectsequence.h"
#include <typeinfo>

#include <QDebug>

namespace qSynth {

EffectTreeItem* EffectTreeModel::getItem(const QModelIndex &idx) const {
    if(idx.isValid()){
        EffectTreeItem* it = static_cast<EffectTreeItem*>(idx.internalPointer());
        if(it != nullptr) return it;
    }
    return root;
}

EffectTreeModel::EffectTreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    root = new EffectTreeItem(EffectTreeItem::Sequence,new EffectSequence);
    EffectTreeItem* mix = new EffectTreeItem(EffectTreeItem::Mixer,
                                                new Mixer,
                                                root);
    root->insertChild(0, mix);
}

void EffectTreeModel::addEffect(IAudioEffect *e, QModelIndex &idx){
    typedef EffectTreeItem::EffectType ti;
    ti type = ti::Other;
    EffectTreeItem* parent = getItem(idx);
    int newRow = 0;
    bool changedParent = false;

    QModelIndex newIndex = idx;

    if(parent->type == ti::Other) {
        parent = parent->parent;
        newIndex = idx.parent();
        newRow = idx.row() + 1;
    } else changedParent = true;

    if(typeid(*e) == typeid(Mixer))
        type = ti::Mixer;
    else if(typeid(*e) == typeid(EffectSequence))
        type = ti::Sequence;

    parent->insertChild(newRow, new EffectTreeItem(type,e,parent));
    insertRow(newRow,newIndex);

    if(changedParent)
        emit dataChanged(newIndex,newIndex);
}

void EffectTreeModel::removeEffect(QModelIndex &idx){
    if(!idx.isValid()) return;
    EffectTreeItem* par = getItem(idx)->parent;
    if(par == root) return;//Do not remove mixer
    beginRemoveRows(idx,idx.row(),idx.row()+1);
    par->takeChild(idx.row());
    endRemoveRows();
}

int EffectTreeModel::columnCount(const QModelIndex&) const{
    return 1;
}

QVariant EffectTreeModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();
    if(role != Qt::DisplayRole)
        return QVariant();

    EffectTreeItem* it = getItem(index);

    return it->effect->name();
}

IAudioEffect* EffectTreeModel::getRootEffect(){
    return root->effect;
}

QModelIndex EffectTreeModel::index(int row, int column, const QModelIndex &parent) const{
    /*if(!hasIndex(row, column, parent)) return QModelIndex();
    EffectTreeItem* parentItem;
    if(!parent.isValid())
        parentItem = root;
    else
       parentItem = static_cast<EffectTreeItem*>(parent.internalPointer());

    EffectTreeItem* childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row,column,childItem);
    else return QModelIndex();
    */
    if(parent.isValid() && parent.column() != 0)
        return QModelIndex();

    EffectTreeItem* parentItem = getItem(parent);
    EffectTreeItem* childItem = parentItem->child(row);

    if(childItem)
        return createIndex(row,column, childItem);
    else
        return QModelIndex();
}

QModelIndex EffectTreeModel::parent(const QModelIndex &index) const{
    /*
    if(!index.isValid()) return QModelIndex();
    EffectTreeItem* parentItem =
            static_cast<EffectTreeItem*>(index.internalPointer())->parent;
    if(parentItem == root) return QModelIndex();
    else return createIndex(parentItem->row(), 0, parentItem);
    */
    if(!index.isValid())
        return QModelIndex();

    EffectTreeItem* child = getItem(index);
    EffectTreeItem* parent = child->parent;

    if(parent == root)
        return QModelIndex();

    return createIndex(parent->row(), 0, parent);
}

int EffectTreeModel::rowCount(const QModelIndex &parent) const{
    EffectTreeItem* it = getItem(parent);
    return it->children.size();

    /*if(!parent.isValid())
        it = root;
    else it = static_cast<EffectTreeItem*>(parent.internalPointer());

    return it->children.size();*/
}

bool EffectTreeModel::insertRow(int row, const QModelIndex &parent){
    beginInsertRows(parent, row,row+1);
    endInsertRows();
    return true;
}

} // namespace qSynth

