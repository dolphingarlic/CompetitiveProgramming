#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

pair<int, int> visited[2001][2001];
vector<pair<int, int>> graph[2001];
set<pair<pair<int, int>, int>> forbidden;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    FOR(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }
    FOR(i, 0, k) {
        pair<pair<int, int>, int> s;
        cin >> s.first.first >> s.first.second >> s.second;
        forbidden.insert(s);
    }

    priority_queue<pair<pair<int, int>, pair<int, int>>> pq;
    pq.push({{-1, 0}, {1, 1}});
    while (pq.size()) {
        pair<int, int> prev, cost;
        tie(cost, prev) = pq.top();
        pq.pop();

        if (!visited[prev.first][prev.second].first) {
            visited[prev.first][prev.second] = cost;
            if (prev.second == n) {
                cout << -cost.first - 1 << '\n';
                vector<int> stack;
                while (prev.first) {
                    stack.push_back(prev.second);
                    prev = {visited[prev.first][prev.second].second,
                            prev.first};
                }

                while (stack.size()) {
                    cout << stack.back() << ' ';
                    stack.pop_back();
                }
                return 0;
            }

            for (auto& i : graph[prev.second]) {
                if (forbidden.find({prev, i.first}) == forbidden.end()) {
                    pq.push({{cost.first - i.second, prev.first},
                             {prev.second, i.first}});
                }
            }
        }
    }

    cout << -1;
    return 0;
}