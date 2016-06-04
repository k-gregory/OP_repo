#ifndef QSYNTH_UTIL_SPINLOCK_H
#define QSYNTH_UTIL_SPINLOCK_H

#include <atomic>

namespace qSynth {
namespace util {

class Spinlock
{
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
public:
    bool try_lock();
    void lock();
    void unlock();
};

} // namespace util
} // namespace qSynth

#endif // QSYNTH_UTIL_SPINLOCK_H
