#include "spinlock.h"

namespace qSynth {
namespace util {

bool Spinlock::try_lock(){
    return lock.test_and_set(std::memory_order_acquire);
}

void Spinlock::lock(){
    while(lock.test_and_set(std::memory_order_acquire));
}

void Spinlock::unlock(){
    lock.clear(std::memory_order_release);
}

} // namespace util
} // namespace qSynth

