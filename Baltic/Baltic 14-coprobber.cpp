#include "coprobber.h"
#include <bits/stdc++.h>
using namespace std;
 
vector<int> graph[3 * MAX_N * MAX_N];
bool win[3 * MAX_N * MAX_N];
int deg_in[3 * MAX_N * MAX_N], here, nxt[3 * MAX_N * MAX_N];
 
inline void add_edge(int a, int b, int c, int d, bool cop) {
    graph[2 * (MAX_N * c + d) + 1 - cop].push_back(2 * (MAX_N * a + b) + cop);
    deg_in[2 * (MAX_N * a + b) + cop]++;
}
 
int start(int N, bool A[MAX_N][MAX_N]) {
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
        if (i == j) continue;
        add_edge(i, j, i, j, 1);
        for (int k = 0; k < N; k++) if (A[i][k]) {
            add_edge(i, j, k, j, 1);
            add_edge(j, i, j, k, 0);
        }
    }
 
    queue<int> q; // Reverse BFS
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) for (int k = 0; k < 2; k++) {
        if (!deg_in[2 * (MAX_N * i + j) + k]) {
            q.push(2 * (MAX_N * i + j) + k);
            win[2 * (MAX_N * i + j) + k] = true;
        }
    }
    while (q.size()) {
        int curr = q.front();
        q.pop();
        for (int i : graph[curr]) {
            deg_in[i]--;
            if (!win[i] && ((i & 1) || !deg_in[i])) {
                nxt[i] = (curr / 2) / MAX_N;
                win[i] = true;
                q.push(i);
            }
        }
    }
 
    for (int i = 0; i < N; i++) {
        bool guarantee = true;
        for (int j = 0; j < N; j++) guarantee &= win[2 * (MAX_N * i + j) + 1];
        if (guarantee) {
            here = i;
            return i;
        }
    }
    return -1;
}
 
int nextMove(int R) {
    here = nxt[2 * (MAX_N * here + R) + 1];
    return here;
}