#include <iostream>
#include <uCobegin.h>
using namespace std;

// Counter implemented with no locking (no mutual exclusion)
class Counter {
    int counter;
    public:
        Counter(int init = 0): counter(init) {}
        int dec() { counter--; return counter; }
        int inc() { counter++; return counter; }
        int count() const { return counter; }
};

// AtomicCounter using implicit locking provided by _Monitor (mutual exclusion)
_Monitor AtomicCounter {
    int counter;
    public:
        AtomicCounter(int init = 0): counter(init) {}
        int dec() { counter--; return counter; }
        int inc() { counter++; return counter; }
        int count() { return counter; }
};


int main() {
    {
        Counter c;                      // Init counter
        // Start 2 simultaneous threads to inc and dec count
        COBEGIN
            BEGIN for (unsigned int i = 0; i < 10000000; ++i) c.inc(); END
            BEGIN for (unsigned int i = 0; i < 10000000; ++i) c.dec(); END
        COEND
        cout << c.count() << endl;      // Output varies since no mutual exclusion
    }

    {
        AtomicCounter a;                // Init counter
        // Start 2 simultaneous threads to inc and dec count
        COBEGIN
            BEGIN for (unsigned int i = 0; i < 10000000; ++i) a.inc(); END
            BEGIN for (unsigned int i = 0; i < 10000000; ++i) a.dec(); END
        COEND
        cout << a.count() << endl;      // Output is ALWAYS 0 due to mutual exclusion provided by monitor
    }
}