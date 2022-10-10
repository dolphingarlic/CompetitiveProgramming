#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int n, t, cmp[2001 * 2001];
pair<int, int> vert[2001], horiz[2001];
vector<int> graph[2001 * 2001];
bool visited[2001 * 2001];

int find(int A) { return cmp[A] = A == cmp[A] ? A : find(cmp[A]); }
void onion(int A, int B) { cmp[find(A)] = find(B); }
int flat(int x, int y) { return x * (2 * n + 1) + y; }
bool inside(int x, int y) { return x >= 0 && x <= 2 * n && y >= 0 && y <= 2 * n; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> t;
    iota(cmp, cmp + (2 * n + 1) * (2 * n + 1), 0);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        vert[x1] = vert[x2] = {y1, y2 - 1};
        horiz[y1] = horiz[y2] = {x1, x2 - 1};
    }
    for (int x = 0; x <= 2 * n; x++) {
        for (int y = 0; y <= 2 * n; y++) {
            if (inside(x + 1, y) && (y < vert[x + 1].first || y > vert[x + 1].second))
                onion(flat(x, y), flat(x + 1, y));
            if (inside(x - 1, y) && (y < vert[x].first || y > vert[x].second))
                onion(flat(x, y), flat(x - 1, y));
            if (inside(x, y + 1) && (x < horiz[y + 1].first || x > horiz[y + 1].second))
                onion(flat(x, y), flat(x, y + 1));
            if (inside(x, y - 1) && (x < horiz[y].first || x > horiz[y].second))
                onion(flat(x, y), flat(x, y - 1));
        }
    }
    for (int x = 0; x <= 2 * n; x++) {
        for (int y = 0; y <= 2 * n; y++) {
            if (inside(x + 1, y) && find(flat(x, y)) != find(flat(x + 1, y))) {
                graph[find(flat(x, y))].push_back(find(flat(x + 1, y)));
                graph[find(flat(x + 1, y))].push_back(find(flat(x, y)));
            }
            if (inside(x - 1, y) && find(flat(x, y)) != find(flat(x - 1, y))) {
                graph[find(flat(x, y))].push_back(find(flat(x - 1, y)));
                graph[find(flat(x - 1, y))].push_back(find(flat(x, y)));
            }
            if (inside(x, y + 1) && find(flat(x, y)) != find(flat(x, y + 1))) {
                graph[find(flat(x, y))].push_back(find(flat(x, y + 1)));
                graph[find(flat(x, y + 1))].push_back(find(flat(x, y)));
            }
            if (inside(x, y - 1) && find(flat(x, y)) != find(flat(x, y - 1))) {
                graph[find(flat(x, y))].push_back(find(flat(x, y - 1)));
                graph[find(flat(x, y - 1))].push_back(find(flat(x, y)));
            }
        }
    }
    queue<pair<int, bool>> q;
    int black = 0, white = 0;
    q.push({find(0), false});
    visited[find(0)] = true;
    while (q.size()) {
        int curr, colour;
        tie(curr, colour) = q.front();
        if (colour) black++; else white++;
        q.pop();
        for (int i : graph[curr]) if (!visited[i]) {
            visited[i] = true;
            q.push({i, !colour});
        }
    }
    if (t == 2) cout << white << ' ' << black << '\n';
    else cout << white + black << '\n';
}
