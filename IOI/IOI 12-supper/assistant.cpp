#include "assistant.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

set<pair<int, int>> scaffold;
int on_scaffold[100000];

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
