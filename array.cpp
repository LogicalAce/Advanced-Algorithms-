#include <iostream>
using namespace std;

int main() {
    int n, target;

    
    cout << "Enter number of elements: ";
    cin >> n;

    int nums[10000];  

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter target value: ";
    cin >> target;

    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                cout << "Indices: [" << i << ", " << j << "]" << endl;
                return 0;  
            }
        }
    }

    cout << "No solution found." << endl;
    return 0;
}
