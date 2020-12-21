#include <iostream>
#include <uCobegin.h>
using namespace std;

const int maxlen = 20;

_Task BoundedBuffer {
    int front = 0, back = 0, count = 0;
    int elements[maxlen];
    public:
        _Nomutex int query() const { return count; }
        void insert(int elem) {
            elements[back] = elem;
        }
        int remove() {
            return elements[front];
        }

    protected:
        void main() {
            for (;;) {
                _Accept(~BoundedBuffer) {
                    break;
                } or _When(count != 20) _Accept(insert) {
                    back = (back + 1) % maxlen;
                    count++;
                } or _When(count != 0) _Accept(remove) {
                    front = (front + 1) % maxlen;
                    count--;
                }
            }
        }
};

int main() {
    BoundedBuffer b;
    COBEGIN
        BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.insert(1); END
        BEGIN for (unsigned int i = 0; i < 10000000; ++i) b.remove();  END
    COEND
    cout << b.query() << endl;  // return 0 after complete
}
