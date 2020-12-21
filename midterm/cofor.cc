#include <uCobegin.h>
#include <iostream>
using namespace std;

int main() {
    const int rows = 10, cols = 10;
    int matrix[rows][cols] = {
        23,10,5,7,
        -1,6,11,20,
        56,-13,6,0
        -2,8,-5,1
    };
    int subtotals[rows], total = 0;

    // for (int r = 0; r < rows; ++r)
    COFOR(r, 0, rows, 
        subtotals[r] = 0;
        for (int c = 0; c < cols; ++c) {
            subtotals[r] += matrix[r][c];
        }
    ); // wait for threads to complete


    for (int r = 0; r < rows; ++r) {
        total += subtotals[r];
    }
    
    cout << total << endl;
}