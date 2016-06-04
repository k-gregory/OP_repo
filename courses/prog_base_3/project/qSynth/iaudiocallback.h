#ifndef IAUDIOCALLBACK
#define IAUDIOCALLBACK

namespace qSynth{

class IAudioCallback{
public:
    virtual void fillBuffer(float* buffer, unsigned long frames) = 0;
};

}

#endif // IAUDIOCALLBACK

