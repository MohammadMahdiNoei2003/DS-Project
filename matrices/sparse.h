#include <iostream>
#include <vector>

using namespace std;
using vector;

class SparseMatrix {
    private:
        vector<double> val;
        vector<int> col_ind;
        vector<int> row_ptr;
        int rows, cols;

    public:
        SparseMatrix(int rows, int cols) : rows(rows), cols(cols) {
            row_ptr.push_back(0);
        }
}