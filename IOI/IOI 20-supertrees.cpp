/*
IOI 2020 Supertrees
- Just make a bunch of jellyfish
- If any 3 appears in the input, return 0
- Complexity: O(N^2)
*/

#include "supertrees.h"
#include <bits/stdc++.h>
using namespace std;

int cmp[1000];
bool used[1000];
vector<pair<int, int>> has[4];
vector<int> cn[1000];

int find(int A) {
    while (A != cmp[A]) A = cmp[A], cmp[A] = cmp[cmp[A]];
    return A;
}

void onion(int A, int B) { cmp[find(A)] = find(B); }

int construct(vector<vector<int>> p) {
    int n = p.size();

    for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) {
        has[p[i][j]].push_back({i, j});
    }

    vector<vector<int>> ans(n, vector<int>(n, 0));

    iota(cmp, cmp + n, 0);
    for (pair<int, int> i : has[1]) onion(i.first, i.second);
    for (int i = 0; i < n; i++) cn[find(i)].push_back(i);
    for (int i = 0; i < n; i++) {
        if (!cn[i].size()) continue;
        for (int j = 1; j < cn[i].size(); j++) {
            ans[cn[i][j]][cn[i][0]] = ans[cn[i][0]][cn[i][j]] = 1;
            used[cn[i][j]] = true;
        }
        cn[i].clear();
    }

    for (pair<int, int> i : has[2]) onion(i.first, i.second);
    for (int i = 0; i < n; i++) if (!used[i]) cn[find(i)].push_back(i);
    for (int i = 0; i < n; i++) {
        if (cn[i].size() < 2) {
            cn[i].clear();
            continue;
        }
        if (cn[i].size() == 2) return 0;
        ans[cn[i][0]][cn[i].back()] = ans[cn[i].back()][cn[i][0]] = 1;
        for (int j = 1; j < cn[i].size(); j++)
            ans[cn[i][j]][cn[i][j - 1]] = ans[cn[i][j - 1]][cn[i][j]] = 1;
        cn[i].clear();
    }

    if (has[3].size()) return 0;
    for (pair<int, int> i : has[0]) if (find(i.first) == find(i.second)) return 0;
    build(ans);
    return 1;
}