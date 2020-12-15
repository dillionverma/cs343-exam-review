#include <iostream>
using namespace std;

/*
The goal of this program is to print "S2" (from T2) before "S1" (from T1)
using only mutex and syncronization locks
*/

bool done = false;                      // global signal

_Task T1 {
    uOwnerLock &mlk;
    uCondLock &clk;

    void main() {
        mlk.acquire();                  // prevent lost signal
        if (!done) {                    // if signal not occured yet, then
            clk.wait(mlk);              // atomic wait + release mlk
                                        // mlk is implicitly acquired by clk when done waiting
        }
        mlk.release();                  // release mlk
        cout << "S1" << endl;           // PRINT
    }
    public:
        T1(uOwnerLock &mlk, uCondLock &clk): mlk(mlk), clk(clk) {}
};


_Task T2 {
    uOwnerLock &mlk;
    uCondLock &clk;

    void main() {
        cout << "S2" << endl;           // PRINT
        mlk.acquire();                  // prevent lost signal
        done = true;                    // fire signal
        clk.signal();                   // signal lost if clk is not waiting in T1
        mlk.release();                  
    }
    public:
        T2(uOwnerLock &mlk, uCondLock &clk): mlk(mlk), clk(clk) {}
};


int main() {
    uOwnerLock mlk;     // mutex lock
    uCondLock clk;      // syncronization lock
    T1 t1(mlk, clk);    // Start T1
    T2 t2(mlk, clk);    // Start T2
}