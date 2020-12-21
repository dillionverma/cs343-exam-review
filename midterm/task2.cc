#include <iostream>
#include <memory>
using namespace std;

_Task Adder {
    int * row, cols, &subtotal;
    void main() {
        for (int c = 0; c < cols; ++c) subtotal += row[c];
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
    int subtotals[rows] = {0};
    int total = 0;

    {
        unique_ptr<Adder> adders[rows];
        for (int r = 0; r < rows; ++r) {
            adders[r] = make_unique<Adder>(matrix[r], cols, subtotals[r]);
        }
    }

    for (int r = 0; r < rows; ++r) {
        total += subtotals[r];
    }
    
    cout << total << endl;
}