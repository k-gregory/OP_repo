#ifndef SDLINPUTOBSERVER_H
#define SDLINPUTOBSERVER_H

namespace atm{

#include <vector>

template<typename T>
class Observer{
protected:
    virtual void observe_handle(const T& e) = 0;
};

template<typename T>
class Observable{
    typedef Observer<T> Observer;
public:

protected:
    void notify_observers(const T& e){
        for(Observer* o : observers)
            o->observe_handle(e);
    }
private:
    std::vector<Observer*> observers;
};

}

#endif //SDLINPUTOBSERVER_H
