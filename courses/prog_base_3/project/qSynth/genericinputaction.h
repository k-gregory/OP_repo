#ifndef QSYNTH_GENERICINPUTACTION_H
#define QSYNTH_GENERICINPUTACTION_H


namespace qSynth {

struct GenericInputAction
{
    enum ActionType{
        KeyPress = 0,
        KeyRelease,
        SpecialAction,
    };
    ActionType type;
    int key;
    int specialInfo[10] = {0};
};

} // namespace qSynth

#endif // QSYNTH_GENERICINPUTACTION_H
