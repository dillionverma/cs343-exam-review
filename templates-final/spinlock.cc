#include <iostream>
using namespace std;

/*
The goal of this program is to print "S2" (from T2) before "S1" (from T1)
using only spinlocks
*/

_Task T1 {
    uLock &lock;
    void main() {
        lock.acquire();                 // cannot acquire since lock is initially closed - busy waiting using CPU time - eventually yields
        cout << "S1" << endl;           // PRINT
        lock.release();                 // release lock when complete
    }
    public:
        T1(uLock &lock): lock(lock) {}
};


_Task T2 {
    uLock &lock;
    void main() {
        cout << "S2" << endl;           // PRINT
        lock.release();                 // release lock, let T1 acquire immediately
    }
    public:
        T2(uLock &lock): lock(lock) {}
};


int main() {
    uLock lock(0);      // closed lock (yielding enabled)
    T1 t1(lock);        // Start T1 
    T2 t2(lock);        // Start T2
}