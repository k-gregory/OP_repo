#include "inputlistmodel.h"
#include <algorithm>

namespace qSynth {

InputListModel::InputListModel()
{
}

int InputListModel::rowCount(const QModelIndex&) const{
    return inputs.size();
}

QVariant InputListModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || role != Qt::DisplayRole) return QVariant();

    return inputs.at(index.row()).name;
}

bool InputListModel::insertRow(int row, const QModelIndex &parent){
    beginInsertRows(parent, row,row+1);
    endInsertRows();
    return true;
}

bool InputListModel::addInput(IGenericInput *i, QString name){
    InputInfo newIn = {i,name};
    if(std::find_if(inputs.begin(),inputs.end(),[&name](InputInfo& o){
        return name == o.name;
    }) != inputs.end()) return false;
    insertRow(inputs.size(),QModelIndex());
    inputs.push_back({i,name});
    return true;
}

std::vector<GenericInputAction> InputListModel::getMultiplexedInput(){
    std::vector<GenericInputAction> multiplexed;
    std::vector<GenericInputAction> to_multiplex;
    for(InputInfo& ii : inputs){
        if(!ii.i->hasInput()) continue;
        to_multiplex = ii.i->pollInput();
        multiplexed.insert(multiplexed.end(),to_multiplex.begin(),to_multiplex.end());
        to_multiplex.clear();
    }
    return multiplexed;
}

} // namespace qSynth

