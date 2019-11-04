#include "grader.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

set<pair<int, int>> scaffold;
map<int, int> scaffold_map;
queue<int> occurrences[100000];
int swap_sequence[100000], on_scaffold[100000], active[200000];

void ComputeAdvice(int *C, int N, int K, int M) {
    FOR(i, 0, N) occurrences[C[i]].push(i);
    FOR(i, 0, N) occurrences[i].push(INT_MAX);

    FOR(i, 0, K) {
        scaffold.insert({-occurrences[i].front(), i});
        on_scaffold[i] = true;
    }

    FOR(i, 0, N) {
        if (on_scaffold[C[i]]) {
            swap_sequence[i] = C[i];
            scaffold.erase({-occurrences[C[i]].front(), C[i]});
        } else {
            swap_sequence[i] = (*scaffold.begin()).second;
            on_scaffold[(*scaffold.begin()).second] = false;
            scaffold.erase(scaffold.begin());
        }
        occurrences[C[i]].pop();
        scaffold.insert({-occurrences[C[i]].front(), C[i]});
        on_scaffold[C[i]] = true;
    }

    FOR(i, 0, N) on_scaffold[i] = (i < K);

    FOR(i, 0, K) scaffold_map[i] = i;
    FOR(i, 0, N) {
        if (on_scaffold[C[i]]) active[scaffold_map[C[i]]] = true;
        else on_scaffold[swap_sequence[i]] = false;
        scaffold_map[C[i]] = i + K;
        on_scaffold[C[i]] = true;
    }

    FOR(i, 0, N + K) WriteAdvice(active[i]);
}

void Assist(unsigned char *A, int N, int K, int R) {
    FOR(i, 0, K) {
        scaffold.insert({A[i], i});
        on_scaffold[i] = A[i] + 1;
    }

    FOR(i, K, N + K) {
        int nxt = GetRequest();
        if (on_scaffold[nxt]) {
            scaffold.erase({on_scaffold[nxt] - 1, nxt});
            scaffold.insert({A[i], nxt});
        } else {
            PutBack((*scaffold.begin()).second);
            on_scaffold[(*scaffold.begin()).second] = 0;
            scaffold.erase(scaffold.begin());
            scaffold.insert({A[i], nxt});
        }
        on_scaffold[nxt] = A[i] + 1;
    }
}
