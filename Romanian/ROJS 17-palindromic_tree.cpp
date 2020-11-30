/*
ROJS 2017 Palidromic Tree
- The pattern 001011001011... has at most 8 palindromes
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    cout << min(n, 8) << '\n';
    for (int i = 0; i < n; i++) cout << "001011"[i % 6];
    return 0;
}