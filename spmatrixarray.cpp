#include <iostream>
using namespace std;

int main() {
    int rows, cols, num;
    cout << "Enter rows, cols, and number of nonzero elements: ";
    cin >> rows >> cols >> num;

    int row[num], col[num], val[num];

    cout << "Enter nonzero elements as (row col value):\n";
    for (int i = 0; i < num; i++)
        cin >> row[i] >> col[i] >> val[i];

    cout << "\nSparse Matrix in Triplet Form:\n";
    cout << "Row  Col  Value\n";
    for (int i = 0; i < num; i++)
        cout << row[i] << "    " << col[i] << "    " << val[i] << endl;

    cout << "\nFull Matrix Representation:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool found = false;
            for (int k = 0; k < num; k++) {
                if (row[k] == i && col[k] == j) {
                    cout << val[k] << " ";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "0 ";
        }
        cout << endl;
    }

    return 0;
}
