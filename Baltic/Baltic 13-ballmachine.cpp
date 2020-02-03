#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    int id, order;
};
bool operator<(Node A, Node B) { return A.order < B.order; }

vector<int> graph[100001];
int ancestor[100001][20], least_child[100001], order[100001], cnt = 1;
bool emp[100001];
set<Node> no_ball;

bool cmp(int A, int B) { return least_child[A] < least_child[B]; }

void find_least_children(int node = 0) {
    least_child[node] = node;
    FOR(i, 1, 20) {
        if (!ancestor[node][i - 1]) break;
        ancestor[node][i] = ancestor[ancestor[node][i - 1]][i - 1];
    }

    for (int i : graph[node]) {
        ancestor[i][0] = node;
        find_least_children(i);
        least_child[node] = min(least_child[node], least_child[i]);
    }
}

void dfs(int node = 0) {
    for (int i : graph[node]) dfs(i);
    order[node] = cnt++;
    if (node) no_ball.insert({node, order[node]});
    emp[node] = true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    FOR(i, 1, n + 1) {
        int p;
        cin >> p;
        graph[p].push_back(i);
    }
    find_least_children();
    FOR(i, 1, n + 1) sort(graph[i].begin(), graph[i].end(), cmp);
    dfs();

    while (q--) {
        int t, x;
        cin >> t >> x;
        if (t == 1) {
            FOR(i, 1, x) {
                emp[(*no_ball.begin()).id] = false;
                no_ball.erase(no_ball.begin());
            }
            cout << (*no_ball.begin()).id << '\n';
            emp[(*no_ball.begin()).id] = false;
            no_ball.erase(no_ball.begin());
        } else {
            int lca = x, ans = 0;
            for (int i = 19; ~i; i--) {
                if (ancestor[lca][i] && !emp[ancestor[lca][i]]) {
                    ans += (1 << i);
                    lca = ancestor[lca][i];
                }
            }
            emp[lca] = true;
            no_ball.insert({lca, order[lca]});
            cout << ans << '\n';
        }
    }
    return 0;
}