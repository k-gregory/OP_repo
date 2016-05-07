#ifndef FUNCTIONALSPINLOCK_H
#define FUNCTIONALSPINLOCK_H

#include <atomic>

class FunctionalSpinlock{
public:
    template<typename F>
    inline void on_successfull_lock(F&& func){
        if(lock.test_and_set(std::memory_order_acquire)){
            func();
            lock.clear(std::memory_order_release);
        }
    }

    template<typename F>
    inline void with_lock(F&& func){
        while(lock.test_and_set(std::memory_order_acquire));
        func();
        lock.clear(std::memory_order_release);
    }

private:
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
};

#endif // FUNCTIONALSPINLOCK_H
