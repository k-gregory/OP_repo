#ifndef INSTRUMENTINPUT_H
#define INSTRUMENTINPUT_H

class InstrumentInput
{
public:
    enum class InputType {
        PRESS,
        UNPRESS,
    } type;


    InstrumentInput();
};

#endif // INSTRUMENTINPUT_H
