#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

int bit[100001], nodeat[100001];

void update(int pos, int val, int N) {
    for (; pos <= N; pos += (pos & (-pos))) bit[pos] += val;
}
int query(int pos, int N) {
    int ans = 0;
    for (; pos > 0; pos -= (pos & (-pos))) ans += bit[pos];
    return ans;
}
int binsearch(int val, int N) {
    int l = 1, r = N;
    while (l != r) {
        int mid = (l + r) / 2;
        if (query(mid, N) < val)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

vector<int> graph[200001];
int colour[200001], knights[100001];
pair<int, int> maxwins[200001];

int ans_wins = 0, ans_node = 1;

// 0 = All W, 1 = Leftmost B; everthing else W, 2 = B somewhere else
void dfs(int node) {
    if (graph[node].empty()) {
        colour[node] = knights[node];
        maxwins[node] = {0, node};
    } else {
        for (int i : graph[node]) {
            dfs(i);
            if (colour[i] && i != graph[node].back()) colour[node] = 2;
        }
        if (colour[node] != 2) {
            if (colour[graph[node].back()])
                colour[node] = 1;
            else
                colour[node] = 0;
        }

        if (colour[node] < 2) {
            int wins = 0, best = 1;
            for (int i : graph[node]) {
                if (maxwins[i].first + 1 >= wins)
                    wins = maxwins[i].first + 1, best = maxwins[i].second;
            }
            maxwins[node] = {wins, best};
        } else
            maxwins[node] = maxwins[graph[node].back()];
    }

    if (maxwins[node].first > ans_wins)
        ans_wins = maxwins[node].first, ans_node = maxwins[node].second;
    else if (maxwins[node].first == ans_wins)
        ans_node = min(ans_node, maxwins[node].second);
}

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
    for (int i = 1; i <= N; i++) {
        update(i, 1, N);
        nodeat[i] = i;
    }

    int indx = N;
    for (int i = 0; i < C; i++) {
        S[i]++, E[i]++;
        indx++;

        for (int j = E[i]; j > S[i]; j--) {
            int pos = binsearch(j, N);
            graph[indx].push_back(nodeat[pos]);
            update(pos, -1, N);
        }
        int pos = binsearch(S[i], N);
        graph[indx].push_back(nodeat[pos]);
        nodeat[pos] = indx;
    }

    knights[1] = 0;
    for (int i = 0; i < N - 1; i++) knights[i + 2] = (K[i] > R);

    dfs(indx);

    return ans_node - 1;
}
