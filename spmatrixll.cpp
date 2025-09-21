#include <iostream>
using namespace std;

struct Node {
    int row, col, val;
    Node* next;
};

int main() {
    int rows, cols, num;
    cout << "Enter rows, cols, and number of nonzero elements: ";
    cin >> rows >> cols >> num;

    Node* head = NULL;

    cout << "Enter nonzero elements (row col value):\n";
    for (int i = 0; i < num; i++) {
        int r, c, v;
        cin >> r >> c >> v;
        Node* n = new Node{r, c, v, head};
        head = n;
    }

    cout << "\nSparse Matrix (Linked List):\n";
    cout << "Row Col Val\n";
    for (Node* t = head; t != NULL; t = t->next)
        cout << t->row << "   " << t->col << "   " << t->val << endl;

    cout << "\nFull Matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Node* t = head;
            int found = 0;
            while (t) {
                if (t->row == i && t->col == j) {
                    cout << t->val << " ";
                    found = 1;
                    break;
                }
                t = t->next;
            }
            if (!found) cout << "0 ";
        }
        cout << endl;
    }

    return 0;
}
