#ifndef QSYNTH_IGENERICINPUT_H
#define QSYNTH_IGENERICINPUT_H

#include <vector>

namespace qSynth {

struct Action{
    enum ActionType{
        KeyPress,
        KeyRelease,
        SpecialAction,
    };
    ActionType type;
    int key;
    int specialInfo[10];
};

class IGenericInput
{
public:
    virtual std::vector<Action> poll_input() = 0;
};

} // namespace qSynth

#endif // QSYNTH_IGENERICINPUT_H
