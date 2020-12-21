#include <iostream>
#include <uSemaphore.h>
using namespace std;

/*
The goal of this program is to print "S2" (from T2) before "S1" (from T1)
using only binary semaphores

Notice how much simpler it is than using mutex and syncronization locks (lock.cc)
*/


_Task T1 {
    uSemaphore &lock;
    void main() {
        lock.P();                       // wait since lock initially closed
        cout << "S1" << endl;           // PRINT
        lock.V();                       // release
    }
    public:
        T1(uSemaphore &lock): lock(lock) {}
};


_Task T2 {
    uSemaphore &lock;
    void main() {
        cout << "S2" << endl;           // PRINT     
        lock.V();                       // release
    }
    public:
        T2(uSemaphore &lock): lock(lock) {}
};


int main() {
    uSemaphore lock(0);     // closed
    T1 t1(lock);            // Start T1
    T2 t2(lock);            // Start T2
}