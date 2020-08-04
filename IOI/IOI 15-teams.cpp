/*
IOI 2015 Teams
- We use sqrt decomposition. In both algorithms, assume the teams are sorted
- Algorithm 1: O((N + M) log N) per query
    - Sort the kids by A
    - Process the teams in increasing order of size
    - Greedily assign the available kids with smallest B to the current team
    - Store the available kids in a priority queue for efficiency
- Algorithm 2: O(M^2 log N) per query
    - By Hall's theorem, a matching is possible iff *insert condition*
    - We thus want to see if any subset of teams breaks that condition
    - Let dp[i] = The minimum (No. of available kids) - (Sum of values in subset)
                  for some subset of the first i teams including i
                = min(dp[j] + (No. of kids (A, B) satisfying K[j] < A <= K[i] and B >= K[i]))
    - We can find the second value in the dp using a persistent segtree
      acting as a static 2D segtree
    - We can then compute dp naively
- Complexity: O(S sqrt(N) log N)
*/

#include "teams.h"

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e5, MAX_SEG = 2e7, B_SIZE = 947;

int N, cnt = 1, seg_val[MAX_SEG], left_c[MAX_SEG], right_c[MAX_SEG];

struct Segtree {
    map<int, int> points[MAX_N + 1];
    int roots[MAX_N + 2];

    void build() {
        for (int i = 1; i <= N; i++) {
            roots[i + 1] = roots[i];
            for (pair<int, int> j : points[i]) update(j.first, j.second, roots[i + 1]);
        }
    }

    void update(int pos, int val, int &node, int l = 1, int r = N) {
        seg_val[cnt] = seg_val[node] + val;
        left_c[cnt] = left_c[node];
        right_c[cnt] = right_c[node];
        node = cnt++;

        if (l == r) return;
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, val, right_c[node], mid + 1, r);
        else update(pos, val, left_c[node], l, mid);
    }

    int query(int a, int b, int node, int l, int r) {
        if (a > r || b < l) return 0;
        if (a <= l && b >= r) return seg_val[node];
        int mid = (l + r) / 2;
        return query(a, b, left_c[node], l, mid) + query(a, b, right_c[node], mid + 1, r);
    }
    int query(int a1, int a2, int b1) {
        return query(a1, a2, roots[N + 1], 1, N) - query(a1, a2, roots[b1], 1, N);
    }
} segtree;

int dp[MAX_N];
pair<int, int> students[MAX_N];

void init(int N, int A[], int B[]) {
    ::N = N;
    for (int i = 0; i < N; i++) {
        students[i] = {A[i], B[i]};
        segtree.points[B[i]][A[i]]++;
    }
    segtree.build();
    sort(students, students + N);
}

int can(int M, int K[]) {
    sort(K, K + M);
    if (M > B_SIZE) {
        priority_queue<int> pq;
        for (int i = 0, j = 0; i < M; i++) {
            while (j < N && students[j].first <= K[i]) pq.push(-students[j++].second);
            while (pq.size() && -pq.top() < K[i]) pq.pop();
            if (pq.size() < K[i]) return 0;
            for (int k = 0; k < K[i]; k++) pq.pop();
        }
        return 1;
    } else {
        for (int i = 0; i < M; i++) {
            dp[i] = segtree.query(1, K[i], K[i]) - K[i];
            for (int j = 0; j < i; j++) {
                dp[i] = min(dp[i], dp[j] + segtree.query(K[j] + 1, K[i], K[i]) - K[i]);
            }
            if (dp[i] < 0) return 0;
        }
        return 1;
    }
}
