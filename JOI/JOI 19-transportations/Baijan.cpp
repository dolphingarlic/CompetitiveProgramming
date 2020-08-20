#include "Baijan.h"

#include <bits/stdc++.h>
using namespace std;

namespace {
int N, stage = 0, cnt, a_shortest, mx_so_far;
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

    while (pq.size() && visited[pq.top().second]) pq.pop();
    if (pq.size()) cand = {-pq.top().first, pq.top().second};
    else cand = {mx_so_far + 511, -1};

    cnt = stage = a_shortest = 0;
}
}  // namespace

void InitB(int N, int B, vector<int> S, vector<int> T, vector<int> D) {
    ::N = N;
    shortest.resize(N);
    for (int i = 0; i < B; i++) {
        graph[S[i]].push_back({T[i], D[i]});
        graph[T[i]].push_back({S[i], D[i]});
    }
    reset();
}

void ReceiveB(bool y) {
    if (stage == 0) {
        a_shortest |= y << cnt++;
        if (cnt == 9) {
            if (a_shortest > cand.first - mx_so_far) {
                for (int i = 0; i < 9; i++) SendB(((cand.first - mx_so_far) & (1 << i)) >> i);
                for (int i = 0; i < 11; i++) SendB((cand.second & (1 << i)) >> i);
                reset();
            } else {
                for (int i = 0; i < 9; i++) SendB(1);
                cnt = 0;
                cand = {a_shortest + mx_so_far, 0};
                stage++;
            }
        }
    } else if (stage == 1) {
        cand.second |= y << cnt++;
        if (cnt == 11) reset();
    }
}
