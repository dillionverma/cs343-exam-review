#include <uActor.h>
#include <iostream>
using namespace std;

_Actor Adder {
    int * row, cols, &subtotal;
    Allocation receive( Message &m) {
        subtotal = 0;
        for (int c = 0; c < cols; ++c) subtotal += row[c];
        return Delete;
    }
  public:
    Adder(int row[], int cols, int & subtotal): row(row), cols(cols), subtotal(subtotal) {}
};

int main() {
    const int rows = 10, cols = 10;
    int matrix[rows][cols] = {
        23,10,5,7,
        -1,6,11,20,
        56,-13,6,0
        -2,8,-5,1
    };
    int subtotals[rows], total = 0;

    uActorStart();
    for (int r = 0; r < rows; ++r) {
        *new Adder(matrix[r], cols, subtotals[r]) | uActor::startMsg;
    }
    uActorStop();

    for (int r = 0; r < rows; ++r) {
        total += subtotals[r];
    }
    
    cout << total << endl;
}