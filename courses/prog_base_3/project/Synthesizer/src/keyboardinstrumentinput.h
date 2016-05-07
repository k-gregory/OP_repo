#ifndef KEYBOARDINSTRUMENTINPUT_H
#define KEYBOARDINSTRUMENTINPUT_H

#include "instrumentinputdevice.h"

class KeyboardInstrumentInput : private InstrumentInputDevice
{
public:
    KeyboardInstrumentInput();
    std::vector<InstrumentInput> poll_input() override;
};

#endif // KEYBOARDINSTRUMENTINPUT_H
