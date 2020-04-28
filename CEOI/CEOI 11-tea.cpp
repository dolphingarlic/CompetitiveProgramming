#include <bits/stdc++.h>
using namespace std;

pair<int, int> a[1000001];
vector<vector<int>> teams;
priority_queue<pair<int, int>> pq;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    sort(a + 1, a + n + 1);

    while (n) {
        if (a[n].first > n) {
            int sz, idx;
            tie(sz, idx) = pq.top();
            pq.pop();
            teams[idx].push_back(a[n--].second);
            pq.push({sz - 1, idx});
        } else {
            int ptr = n;
            teams.push_back({});
            while (ptr && n - ptr != a[n].first) teams.back().push_back(a[ptr--].second);
            pq.push({-teams.back().size(), teams.size() - 1});
            n = ptr;
        }
    }

    printf("%d\n", teams.size());
    for (vector<int> i : teams) {
        printf("%d", i.size());
        for (int j : i) printf(" %d", j);
        printf("\n");
    }
    return 0;
}