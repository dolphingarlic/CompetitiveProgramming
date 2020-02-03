#include <bits/stdc++.h>
#include "friend.h"
using namespace std;

int colour[100001], dp[2][100001], c[100001];
vector<int> graph[100001];

void dfs(int node) {
    dp[0][node] = c[node];
    for (int i : graph[node]) {
        dfs(i);
        if (!colour[i])
            dp[1][node] += dp[0][i], dp[0][node] += dp[1][i];
        else if (colour[i] == 1)
            dp[0][node] += dp[0][i], dp[1][node] += dp[1][i];
        else
            dp[1][node] += dp[1][i], dp[0][node] += dp[1][i];
    }
    int curr = dp[1][node];
    dp[0][node] = max(dp[0][node], curr);

    for (int i : graph[node]) {
        if (!colour[i])
            curr += dp[1][i] - dp[0][i];
        else 
            curr += dp[0][i] - dp[1][i];
        dp[0][node] = max(dp[0][node], curr);
        if (colour[i] == 2) curr += dp[1][i] - dp[0][i];
    }
}

int findSample(int n, int confidence[], int host[], int protocol[]) {
    c[0] = confidence[0];
    for (int i = 1; i < n; i++) {
        c[i] = confidence[i];
        colour[i] = protocol[i];
        graph[host[i]].push_back(i);
    }
    dfs(0);
    return dp[0][0];
}
