#include "spinlock.h"

namespace qSynth {
namespace util {

bool Spinlock::try_lock(){
    return !a_lock.test_and_set(std::memory_order_acquire);
}

void Spinlock::lock(){
    while(a_lock.test_and_set(std::memory_order_acquire));
}

void Spinlock::unlock(){
    a_lock.clear(std::memory_order_release);
}

} // namespace util
} // namespace qSynth

