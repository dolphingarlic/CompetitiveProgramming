#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

set<ll> hash_set;
vector<int> graph[100000];

ll hash_tree(int node) {

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int v = s.size() / 2 + 1;
        FOR(i, 0, v) graph[i].clear();
        
    }
    return 0;
}