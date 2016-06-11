#ifndef QSYNTH_EFFECTTREEITEM_H
#define QSYNTH_EFFECTTREEITEM_H

#include <QTreeWidgetItem>
#include <QVariant>
#include <vector>
#include "iaudioeffect.h"

namespace qSynth {

class EffectTreeItem
{

public:
    enum EffectType{
        Mixer,
        Sequence,
        Other
    };

    explicit EffectTreeItem(EffectType t, IAudioEffect* effect,EffectTreeItem* parent = nullptr);
    EffectTreeItem* takeChild(unsigned int index);
    void insertChild(unsigned int index, EffectTreeItem* it);
    EffectTreeItem* child(unsigned int row);
    int row();
    EffectTreeItem* parent;
    std::vector<EffectTreeItem*> children;
private:
    EffectType type;
    IAudioEffect* effect;
    bool hasChildren;
};

} // namespace qSynth

#endif // QSYNTH_EFFECTTREEITEM_H
