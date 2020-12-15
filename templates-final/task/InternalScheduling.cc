#include <iostream>
#include <uCobegin.h>
using namespace std;

const int maxlen = 20;

_Task BoundedBuffer {
    int front = 0, back = 0, count = 0;
    int elements[maxlen];
    uCondition full, empty;                     // condition variable queues
    public:
        _Nomutex int query() const { return count; }
        void insert(int elem) {
            if (count == maxlen) empty.wait();  // wait on empty queue
            elements[back] = elem;
        }
        int remove() {
            if (count == 0) full.wait();        // wait on full queue
            return elements[front];
        }
    protected:
        void postInsert() {
            back = (back + 1) % maxlen;
            count++;
        }
        void postRemove() {
            front = (front + 1) % maxlen;
            count--;
        }
        void main() {
            for(;;) {
                _Accept(~BoundedBuffer) {
                    break;
                } or _When(count != maxlen) _Accept(insert) {
                    postInsert();
                    if (!full.empty()) {
                        full.signalBlock();         // NOTE: block current task
                        postRemove();
                    }
                } or _When(count != 0) _Accept(remove) {
                    postRemove();
                    if (!empty.empty()) {
                        empty.signalBlock();        // NOTE: block current task
                        postInsert();
                    }
                } // _Accept
            } // for
        } // main
};

int main() {
    BoundedBuffer b;            // init buffer
    // Start 2 simultaneous threads to insert and remove from buffer
    COBEGIN
        BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.insert(1); END
        BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.remove();  END
    COEND
    cout << b.query() << endl;  // return 0 after complete
}
