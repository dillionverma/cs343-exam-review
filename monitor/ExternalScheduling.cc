#include <iostream>
#include <uCobegin.h>
#include <uSemaphore.h>
using namespace std;

const int maxlen = 20;

_Monitor BoundedBuffer {
    int front = 0, back = 0, count = 0;
    int elements[maxlen];
    public:
        _Nomutex int query() const { return count; }
        void insert(int elem) {
            if (count == maxlen) _Accept(remove);
            elements[back] = elem;
            back = (back + 1) % maxlen;
            count++;
        }
        int remove() {
            if (count == 0) _Accept(insert);
            int elem = elements[front];
            front = (front + 1) % maxlen;
            count--;
            return elem;
        }
};

int main() {
    {
        BoundedBuffer b;

        // TODO: Implement external scheduling of tasks which are inserting and removing
        COBEGIN
            BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.insert(1); END
            BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.remove(); END
        COEND
        cout << b.query() << endl;  // return 0 after complete
    }
}
