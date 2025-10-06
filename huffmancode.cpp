#include <bits/stdc++.h>
using namespace std;

int main() {
    string S;
    cout << "Enter characters (e.g. abcdef): ";
    cin >> S;
    int n = S.size();
    vector<int> freq(n);
    cout << "Enter " << n << " frequencies: ";
    for (int i = 0; i < n; ++i) cin >> freq[i];

    
    vector<string> code(n, "");

    
    vector<pair<int, vector<int>>> groups;
    for (int i = 0; i < n; ++i) groups.push_back({freq[i], {i}});

   
    while (groups.size() > 1) {
        
        sort(groups.begin(), groups.end(),
             [](const pair<int, vector<int>> &a, const pair<int, vector<int>> &b) {
                 return a.first < b.first;
             });

        
        auto g1 = groups[0];
        auto g2 = groups[1];

        
        for (int idx : g1.second) code[idx] = "0" + code[idx];
        for (int idx : g2.second) code[idx] = "1" + code[idx];

        
        vector<int> merged = g1.second;
        merged.insert(merged.end(), g2.second.begin(), g2.second.end());
        int newFreq = g1.first + g2.first;

        
        groups.erase(groups.begin()); 
        groups.erase(groups.begin()); 
        groups.push_back({newFreq, merged});
    }

    
    cout << "\nHuffman codes:\n";
    for (int i = 0; i < n; ++i)
        cout << S[i] << " : " << (code[i].empty() ? "0" : code[i]) << "\n";

    return 0;
}
