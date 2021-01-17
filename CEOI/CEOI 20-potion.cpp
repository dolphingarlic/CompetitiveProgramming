/*
CEOI 2020 The Potion of Great Power
- For each node, store a list of its neighbours (sorted by H[i]) after every C updates affecting it
    - This is because the problemsetters were big meanies who made the memory limit super tight
    - This trick is kinda like the one in IOI 2013 Wombats
    - Also store the C updates that follow it, kinda like sqrt decomposition
- Then just brute force and use 2-pointers/merge sort to answer each query in O(D + C log C) time
- Somehow this works because constants are small??? C = 50 seems to work well
- Complexity: O(U log D + UD/C + Q(D + C log C)) and O(UD/C) memory
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9, C = 50;

int H[100000];
bool odd[100000];
vector<int> u_times[100000];
vector<vector<int>> trust[100000];
struct cmp {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return tie(H[a.second], a.first) < tie(H[b.second], b.first);
    }
};
vector<set<pair<int, int>, cmp>> updates[100000];

void init(int N, int D, int H[]) {
    for (int i = 0; i < N; i++) {
        trust[i].push_back({});
        updates[i].push_back({});
        u_times[i].push_back(0);
        ::H[i] = H[i];
    }
}

vector<int> playback(int s, int t) {
    int ub = upper_bound(u_times[s].begin(), u_times[s].end(), t) - u_times[s].begin() - 1;
    vector<int> orig = trust[s][ub];
    set<pair<int, int>, cmp> upd = updates[s][ub];
    for (int i : orig) odd[i] ^= 1;
    for (pair<int, int> i : upd) {
        if (i.first >= t) continue;
        odd[i.second] ^= 1;
    }
    vector<int> ret1, ret2;
    for (int i : orig) if (odd[i]) ret1.push_back(i), odd[i] = 0;
    for (pair<int, int> i : upd) {
        if (i.first >= t) continue;
        if (odd[i.second]) ret2.push_back(i.second), odd[i.second] = 0;
    }
    vector<int> mrg;
    int ptr1 = 0, ptr2 = 0;
    while (ptr1 < ret1.size() && ptr2 < ret2.size()) {
        if (H[ret1[ptr1]] < H[ret2[ptr2]]) mrg.push_back(ret1[ptr1++]);
        else mrg.push_back(ret2[ptr2++]);
    }
    while (ptr1 < ret1.size()) mrg.push_back(ret1[ptr1++]);
    while (ptr2 < ret2.size()) mrg.push_back(ret2[ptr2++]);
    return mrg;
}

void curseChanges(int U, int A[], int B[]) {
    for (int i = 0; i < U; i++) {
        updates[A[i]].back().insert({i, B[i]});
        updates[B[i]].back().insert({i, A[i]});
        if (updates[A[i]].back().size() == C) {
            trust[A[i]].push_back(playback(A[i], i + 1));
            updates[A[i]].push_back({});
            u_times[A[i]].push_back(i + 1);
        }
        if (updates[B[i]].back().size() == C) {
            trust[B[i]].push_back(playback(B[i], i + 1));
            updates[B[i]].push_back({});
            u_times[B[i]].push_back(i + 1);
        }
    }
}

int question(int x, int y, int v) {
    vector<int> sx = playback(x, v);
    vector<int> sy = playback(y, v);
    int ans = INF;
    for (int xptr = 0, yptr = 0; xptr != sx.size() && yptr != sy.size();) {
        ans = min(ans, abs(H[sx[xptr]] - H[sy[yptr]]));
        if (H[sx[xptr]] <= H[sy[yptr]]) xptr++;
        else yptr++;
    }
    return ans;
}
