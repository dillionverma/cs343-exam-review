#include <iostream>
#include <uCobegin.h>
using namespace std;

const int maxlen = 20;

_Monitor BoundedBuffer {
    int front = 0, back = 0, count = 0;
    int elements[maxlen];
    public:
        _Nomutex int query() const { return count; }
        void insert(int elem);
        int remove();
};

// Notice that insert() calls remove() and vice versa. Hence the functions
// are defined outside the class in order for compilation
void BoundedBuffer::insert(int elem) {
    if (count == maxlen) _Accept(remove);   // External scheduling
    elements[back] = elem;
    back = (back + 1) % maxlen;
    count++;
}

int BoundedBuffer::remove() {
    if (count == 0) _Accept(insert);        // External scheduling
    int elem = elements[front];
    front = (front + 1) % maxlen;
    count--;
    return elem;
}

int main() {
    BoundedBuffer b;            // init buffer
    // Start 2 simultaneous threads to insert and remove from buffer
    COBEGIN
        BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.insert(1); END
        BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.remove();  END
    COEND
    cout << b.query() << endl;  // return 0 after complete
}
