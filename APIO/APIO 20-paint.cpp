/*
APIO 2020 Paint
- Let dp[x][y] = The number of segments until we get a problem if we
                 give the instruction (x, y)
               = dp[(x + 1) % M][y + 1] + 1
- Since sum(f(k)^2) is so smol, we're updating at most ~600 DP values
  for each x
- Also, we don't have to store the first dimension of the DP array entirely
- This means that we can find DP kinda efficiently (idk the complexity)
- Next, just greedily paint the furthest wall segment we have to
- Complexity: O(N MAX_FK)
*/

#include "paint.h"

#include <bits/stdc++.h>
using namespace std;

int dp[2][50002];
vector<int> good[100002];
bool possible[100002];

int minimumInstructions(int N, int M, int K, vector<int> C, vector<int> A, vector<vector<int>> B) {
    for (int i = 0; i < M; i++) for (int j : B[i]) good[j].push_back(i);

    for (int i = N - 1; ~i; i--) {
        for (int j : good[C[i + 2]]) dp[i & 1][j] = 0;
        for (int j : good[C[i]]) {
            dp[i & 1][j] = dp[i + 1 & 1][(j + 1) % M] + 1;
            if (dp[i & 1][j] >= M) possible[i] = true;
        }
    }

    int ans = 0, last_painted = -1;
    for (int i = 0, best = -M; i < N; i++) {
        if (possible[i]) best = i;
        if (i > last_painted) {
            if (best + M == i) return -1;
            ans++;
            last_painted = best + M - 1;
        }
    }
    return ans;
}