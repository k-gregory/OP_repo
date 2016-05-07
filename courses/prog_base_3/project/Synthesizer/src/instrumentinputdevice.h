#ifndef INSTRUMENTINPUTDEVICE_H
#define INSTRUMENTINPUTDEVICE_H

#include "instrumentinput.h"
#include <vector>

class InstrumentInputDevice
{
public:
    virtual std::vector<InstrumentInput> poll_input() = 0;
};

#endif // INSTRUMENTINPUTDEVICE_H
