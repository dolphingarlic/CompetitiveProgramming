/*
IOI 2020 Squares
- Construct the De Bruijn sequence of order 10
- Reconstruct it each time a function is called
- Complexity: O(N^2)
*/

#include "squares.h"

#include <bits/stdc++.h>
using namespace std;

bool visited[1024];
int k, ord[1024], N;
vector<int> de_bruijn;

void dfs(int node) {
    for (int i : {0, 1}) {
        int nxt = node + (i << k - 1);
        if (!visited[nxt]) {
            visited[nxt] = 1;
            dfs(nxt >> 1);
            de_bruijn.push_back(i);
        }
    }
}

vector<int> paint(int n) {
    memset(visited, 0, sizeof visited);
    de_bruijn.clear();
    k = min(10, n);
    dfs(0);
    for (int i = 1; i < k; i++) de_bruijn.push_back(0);
    while (de_bruijn.size() > n) de_bruijn.pop_back();
    for (int i = 0; i <= de_bruijn.size() - k; i++) {
        int hsh = 0;
        for (int j = i; j < i + k; j++) hsh = (hsh << 1) + de_bruijn[j];
        ord[hsh] = i;
    }
    de_bruijn.push_back(k);
    return de_bruijn;
}

int find_location(int n, vector<int> c) {
    memset(visited, 0, sizeof visited);
    de_bruijn.clear();
    k = min(10, n);
    dfs(0);
    for (int i = 0; i <= de_bruijn.size() - k; i++) {
        int hsh = 0;
        for (int j = i; j < i + k; j++) hsh = (hsh << 1) + de_bruijn[j];
        ord[hsh] = i;
    }
    int hsh = 0;
    for (int i = 0; i < c.size(); i++) {
        if (c[i] == -1) return n - i;
        hsh = (hsh << 1) + c[i];
    }
    return ord[hsh];
}
