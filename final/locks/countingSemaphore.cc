#include <iostream>
#include <uSemaphore.h>
using namespace std;

/*
The goal of this program is to print "S3" (from T3) before "S1" (from T1) and "S2" (from T2)
using only counting semaphores
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
        lock.P();                       // wait
        cout << "S2" << endl;           // PRINT     
        lock.V();                       // release
    }
    public:
        T2(uSemaphore &lock): lock(lock) {}
};

_Task T3 {
    uSemaphore &lock;
    void main() {
        cout << "S3" << endl;           // PRINT     
        lock.V();                       // release (T1 continues due to FIFO)
        lock.V();                       // release (T2 continues due to FIFO)
    }
    public:
        T3(uSemaphore &lock): lock(lock) {}
};


int main() {
    uSemaphore lock(0);     // closed
    T1 t1(lock);            // Start T1
    T2 t2(lock);            // Start T2
    T3 t3(lock);            // Start T3
}