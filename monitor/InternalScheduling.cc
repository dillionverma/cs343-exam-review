#include <iostream>
#include <uCobegin.h>
using namespace std;

const int maxlen = 20;

_Monitor BoundedBuffer {
    int front = 0, back = 0, count = 0;
    int elements[maxlen];
    uCondition full, empty;
    public:
        _Nomutex int query() const { return count; }
        void insert(int elem) {
            if (count == maxlen) empty.wait();
            elements[back] = elem;
            back = (back + 1) % maxlen;
            count++;
            full.signal();
        }
        int remove() {
            if (count == 0) full.wait();
            int elem = elements[front];
            front = (front + 1) % maxlen;
            count--;
            empty.signal();
            return elem;
        }
};

int main() {
    {
        BoundedBuffer b; 
        COBEGIN
            BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.insert(1); END
            BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.remove(); END
        COEND
        cout << b.query() << endl;  // return 0 after complete
    }
}
