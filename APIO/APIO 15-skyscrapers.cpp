#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
priority_queue<pair<int, int>> q1;
const int MAXN = 30010;
set<int> v1[MAXN];
vector<pair<int, int>> g[MAXN];
bool visited[MAXN];
int dp[MAXN];
int target;
 
int first, jump;
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int b, p;
        cin >> b >> p;
        if (i == 0) {
            first = b;
            jump = p;
        }
        if (i == 1) {
            target = b;
        }
 
        v1[b].insert(p);
    }
    for (int i = 0; i <= n; i++) {
        for (int x : v1[i]) {
            int b = i;
            int p = x;
            int count = 1;
            for (int j = b + p; j <= n; j += p) {
                if (v1[j].find(p) != v1[j].end()) {
                    g[b].push_back(make_pair(j, count));
                    break;
                }
                g[b].push_back(make_pair(j, count));
                count++;
            }
            count = 1;
            for (int j = b - p; j >= 0; j -= p) {
                if (v1[j].find(p) != v1[j].end()) {
                    g[b].push_back(make_pair(j, count));
                    break;
                }
                g[b].push_back(make_pair(j, count));
                count++;
            }
        }
    }
    q1.push(make_pair(0, first));
    for (int i = 0; i <= n; i++) {
        dp[i] = 1e9;
    }
    dp[first] = 0;
 
    while (!q1.empty()) {
        auto hold = q1.top();
        int skyscraper = hold.second;
        int dist = -1 * hold.first;
 
        q1.pop();
        if (skyscraper == target) {
            cout << dist << endl;
            return 0;
        }
        if (visited[skyscraper]) {
            continue;
        }
        visited[skyscraper] = true;
        for (auto x : g[skyscraper]) {
            int w = x.second;
            int to = x.first;
            if (dp[to] > dp[skyscraper] + w) {
                dp[to] = dp[skyscraper] + w;
                q1.push(make_pair(-1 * dp[to], to));
            }
        }
    }
    cout << -1 << endl;
}