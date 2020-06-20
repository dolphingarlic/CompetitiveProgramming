#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int T = 4;

vector<pair<int, int>> edges;
int nodes = 0;

void construct(int n, int l_start, int r_start) {    
    nodes = max(nodes, max(l_start, r_start) + n - 1);

    if (n == 1) {
        edges.push_back({l_start, r_start});
        return;
    }

    int b_size = (n + T - 1) / T, rem = n;
    FOR(i, 0, T) {
        b_size = min(b_size, rem);
        if (!b_size) return;
        FOR(j, 0, n) {
            edges.push_back({l_start + j, nodes + j % b_size});
        }
        construct(b_size, nodes + 1, r_start + n - rem);
        rem -= b_size;
    }
}

int main() {
    FOR(i, 0, 8) {
        ifstream cin(to_string(i) + "-router.in");
        ofstream cout(to_string(i) + "-router.out");

        int n;
        cin >> n;
        edges.clear();
        nodes = 0;
        construct(n, 1, n + 1);
        cout << nodes << ' ' << edges.size() << '\n';
        for (pair<int, int> j : edges) {
            cout << j.first << ' ' << j.second << '\n';
        }

        cin.close();
        cout.close();
    }
    return 0;
}