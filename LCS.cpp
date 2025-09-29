#include <bits/stdc++.h>
using namespace std;

int main() {
    const int MAX = 200;
    char s1[MAX+1], s2[MAX+1];
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    int m = strlen(s1);
    int n = strlen(s2);

 
    static int dp[201][201]; 
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= n; ++j)
            dp[i][j] = 0;

    int maxLen = 0;
    int endPos = 0; 

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endPos = i; 
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    
    cout << "\nDP table (rows = first string, cols = second string)\n\n   ";
    for (int j = 0; j < n; ++j) {
        cout << "  " << s2[j];
    }
    cout << "\n";

    
    for (int i = 0; i <= m; ++i) {
        if (i == 0) cout << "  ";
        else cout << s1[i-1] << " ";
        for (int j = 0; j <= n; ++j) {
            
            cout << setw(2) << dp[i][j] << " ";
        }
        cout << "\n";
    }

    
    string lcs = "";
    if (maxLen > 0) {
        lcs = string(&s1[endPos - maxLen], &s1[endPos]); 
    }

    cout << "\nLongest common substring length = " << maxLen << "\n";
    cout << "One longest common substring: \"" << lcs << "\"\n";

    return 0;
}
