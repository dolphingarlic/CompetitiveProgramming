/*
POI 2009 The Walk of Bytie Boy
- For each node/edge, fix that as the centre of the palindrome and do a BFS to extend it
- Use backtracking to rebuild the actual word
- Complexity: O(N^3 * 26)
*/

#include <bits/stdc++.h>
using namespace std;

pair<pair<int, int>, int> visited[401][401];

vector<int> graph[401][26], rev[401][26];
int p[100];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    cin >> n >> m;
    queue<pair<int, int>> q;
    n++;
    while (--n) {
        q.push({n, n});
        visited[n][n] = {{n, n}, -1};
    }
    while (m--) {
        char c;
        cin >> a >> b >> c;
        graph[a][c - 'a'].push_back(b);
        rev[b][c - 'a'].push_back(a);

        q.push({a, b});
        visited[a][b] = {{a, b}, c - 'a'};
    }

    while (q.size()) {
        tie(a, b) = q.front();
        q.pop();

        for (int c = 0; c < 26; c++)
            for (int i : graph[b][c])
                for (int j : rev[a][c])
                    if (!visited[j][i].first.first)
                        q.push({j, i}), visited[j][i] = {{a, b}, c};
    }

    int d;
    cin >> d;
    for (int i = 0; i < d; i++) {
        cin >> p[i];
        if (i) {
            if (!visited[p[i - 1]][p[i]].first.first)
                cout << "-1\n";
            else {
                string s = "";
                a = p[i - 1], b = p[i];
                while (visited[a][b].first.first != a) {
                    s += 'a' + visited[a][b].second;
                    tie(a, b) = visited[a][b].first;
                }
                cout << 2 * s.size() + (a != b) << ' ' << s;
                if (a != b) cout << char('a' + visited[a][b].second);
                reverse(s.begin(), s.end());
                cout << s << '\n';
            }
        }
    }

    return 0;
}