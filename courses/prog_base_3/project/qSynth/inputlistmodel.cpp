#include "inputlistmodel.h"
#include <algorithm>

namespace qSynth {

InputListModel::InputListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int InputListModel::rowCount(const QModelIndex&) const{
    return inputs.size();
}

QVariant InputListModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || role != Qt::DisplayRole) return QVariant();

    QString data = inputs[index.row()].getName();
    return data;
}

bool InputListModel::insertRow(int row, const QModelIndex &parent){
    beginInsertRows(parent, row,row+1);
    endInsertRows();
    return true;
}

bool InputListModel::addInput(InputListItem& item){
    QString name = item.getName();
    if(std::find_if(inputs.begin(),inputs.end(),[&name](InputListItem& o){
        return name == o.getName();
    }) != inputs.end()) return false;
    insertRow(inputs.size(),QModelIndex());
    inputs.push_back(item);
    return true;
}

void InputListModel::modifyItem(const QModelIndex &idx){    
    if(!idx.isValid()) return;
    inputs.at(idx.row()).modify();
}

std::vector<GenericInputAction> InputListModel::getMultiplexedInput(){
    std::vector<GenericInputAction> multiplexed;
    std::vector<GenericInputAction> to_multiplex;
    for(InputListItem& item : inputs){
        IGenericInput* input = item.getInput();
        if(!input->hasInput()) continue;
        to_multiplex = input->pollInput();
        multiplexed.insert(multiplexed.end(),to_multiplex.begin(),to_multiplex.end());
        to_multiplex.clear();
    }
    return multiplexed;
}

} // namespace qSynth

