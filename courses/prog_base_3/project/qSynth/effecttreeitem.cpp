#include "effecttreeitem.h"

#include "mixer.h"
#include "effectsequence.h"
#include <algorithm>


namespace qSynth {

EffectTreeItem::EffectTreeItem(EffectType t, IAudioEffect* effect, EffectTreeItem* parent)
    : type(t), effect(effect), parent(parent)
{
    if(type == Other) hasChildren = false;
    else hasChildren = true;
}

EffectTreeItem* EffectTreeItem::takeChild(unsigned int index){
    if(index >= children.size()) return nullptr;
    EffectTreeItem* ret = children[index];
    children.erase(children.begin() + index);
    if(type == Mixer){
        static_cast<qSynth::Mixer*>(effect)->removeEffect(index);
    } else if(type == Sequence){
        static_cast<qSynth::EffectSequence*>(effect)->removeEffect(index);
    }

    return ret;
}

void EffectTreeItem::insertChild(unsigned int index,EffectTreeItem* it){
    if(index > children.size()) return;
    children.insert(children.begin() + index, it);
    if(type == Mixer){
        static_cast<qSynth::Mixer*>(effect)->insertEffect(index,it->effect);
    }
    else if(type==Sequence){
        static_cast<qSynth::EffectSequence*>(effect)->insertEffect(index,it->effect);
    }
}

EffectTreeItem* EffectTreeItem::child(unsigned int row){
    if(row >= children.size()) return nullptr;
    return children[row];
}

int EffectTreeItem::row(){
    return std::find(parent->children.begin(),parent->children.end(), this) - parent->children.begin();
}

} // namespace qSynth

