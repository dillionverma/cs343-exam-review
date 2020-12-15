#include <iostream>
#include <uBarrier.h>
using namespace std;

/*
The goal of this program is to print "S1", "S2", "S3" (in any order) BEFORE "S4", "S5", "S6" (in any order)
using only barriers
*/


_Task T1 {
    uBarrier &b;
    void main() {
        cout << "S1" << endl;           // PRINT
        b.block();
        cout << "S4" << endl;           // PRINT
    }
    public:
        T1(uBarrier &b): b(b) {}
};


_Task T2 {
    uBarrier &b;
    void main() {
        cout << "S2" << endl;           // PRINT        
        b.block();
        cout << "S5" << endl;           // PRINT      
    }
    public:
        T2(uBarrier &b): b(b) {}
};

_Task T3 {
    uBarrier &b;
    void main() {
        cout << "S3" << endl;           // PRINT        
        b.block();
        cout << "S6" << endl;           // PRINT      
    }
    public:
        T3(uBarrier &b): b(b) {}
};


int main() {
    uBarrier b(3);      // indicate how many tasks involved in the operation
    T1 t1(b);           // Start T1
    T2 t2(b);           // Start T2
    T3 t3(b);           // Start T3
}