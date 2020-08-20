#include "Azer.h"

#include <bits/stdc++.h>
using namespace std;

namespace {
int N, stage = 0, cnt, b_shortest, mx_so_far;
vector<pair<int, int>> graph[2000];
vector<int> shortest;
priority_queue<pair<int, int>> pq;
bool visited[2000];
pair<int, int> cand = {0, 0};

void reset() {
    visited[cand.second] = true;
    shortest[cand.second] = cand.first;
    mx_so_far = cand.first;
    for (pair<int, int> i : graph[cand.second])
        pq.push({-cand.first - i.second, i.first});
    N--;

    if (!N) return;

    while (pq.size() && visited[pq.top().second]) pq.pop();
    if (pq.size()) cand = {-pq.top().first, pq.top().second};
    else cand = {mx_so_far + 511, -1};

    for (int i = 0; i < 9; i++) SendA(((cand.first - mx_so_far) & (1 << i)) >> i);
    cnt = stage = b_shortest = 0;
}
}  // namespace

void InitA(int N, int A, vector<int> U, vector<int> V, vector<int> C) {
    ::N = N;
    shortest.resize(N);
    for (int i = 0; i < A; i++) {
        graph[U[i]].push_back({V[i], C[i]});
        graph[V[i]].push_back({U[i], C[i]});
    }
    reset();
}

void ReceiveA(bool x) {
    if (stage == 0) {
        b_shortest |= x << cnt++;
        if (cnt == 9) {
            if (b_shortest == 511) {
                for (int i = 0; i < 11; i++) SendA((cand.second & (1 << i)) >> i);
                reset();
            } else {
                stage++;
                cand = {mx_so_far + b_shortest, 0};
                cnt = 0;
            }
        }
    } else {
        cand.second |= x << cnt++;
        if (cnt == 11) reset();
    }
}

vector<int> Answer() {
    return shortest;
}
