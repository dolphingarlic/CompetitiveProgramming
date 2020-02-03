/*
APIO 2011 Find the Path
- Firstly, notice that N is small so O(N^2 log N^2) should pass
- Secondly, since coordinates are huge but we only care about distances,
  we can compress the grid
    - This leaves us with O(N^2) possible points and O(N^2) possible edges
- From this, we can construct our graph
    - First, connect adjacent points on the perimeter of each rectangle
    - Next, connect points between rectangles if they lie on a line parallel
      to the axes and have nothing between them
        - We do this separately for horizontal and vertical lines
        - A simple line sweep suffices (since the points can be ordered)
            - Basically keep a counter and each time we enter/exit a rectangle
              (even if we're just on the perimeter), increment/decrement it
            - When the counter is 0, join the current point with the previously
              visited point
- After we have our graph, we can just run Dijkstra
- Complexity: O(N^2 log N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
    Rect(int a = 0, int b = 0, int c = 0, int d = 0): x1(a), y1(b), x2(c), y2(d) {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
    }
} rects[1005];

vector<int> xs, ys;

int idx(int val, vector<int> vec) { return lower_bound(vec.begin(), vec.end(), val) - vec.begin(); }

struct Node {
    int x, y;
    operator int() const { return x * ys.size() + y; }
    Node(int a = 0, int b = 0): x(a), y(b) {}
};

bool cmp_x(pair<Node, int> a, pair<Node, int> b) {
    if (a.first.y == b.first.y) return a.first.x < b.first.x;
    return a.first.y < b.first.y;
}
bool cmp_y(pair<Node, int> a, pair<Node, int> b) {
    if (a.first.x == b.first.x) return a.first.y < b.first.y;
    return a.first.x < b.first.x;
}

ll dist(Node a, Node b) { return abs(xs[a.x] - xs[b.x]) + abs(ys[a.y] - ys[b.y]); }

vector<Node> graph[5000001];
bool visited[5000001];

ll dijkstra(Node src, Node dest) {
    priority_queue<pair<ll, Node>> pq;
    pq.push({0, src});
    while (pq.size()) {
        ll d = pq.top().first;
        Node curr = pq.top().second;
        pq.pop();
        if (curr == dest) return -d;
        if (!visited[curr]) {
            visited[curr] = true;
            for (Node i : graph[curr]) pq.push({d - dist(curr, i), i});
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int sx, sy, dx, dy;
        cin >> sx >> sy >> dx >> dy;
        int n;
        cin >> n;
        FOR(i, 0, n) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            rects[i] = Rect(a, b, c, d);
        }
        rects[n++] = Rect(sx, sy, sx, sy);
        rects[n++] = Rect(dx, dy, dx, dy);

        // Coordinate compression
        xs.clear(); ys.clear();
        FOR(i, 0, n) {
            xs.push_back(rects[i].x1); xs.push_back(rects[i].x2);
            ys.push_back(rects[i].y1); ys.push_back(rects[i].y2);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        FOR(i, 0, n) {
            rects[i].x1 = idx(rects[i].x1, xs);
            rects[i].x2 = idx(rects[i].x2, xs);
            rects[i].y1 = idx(rects[i].y1, ys);
            rects[i].y2 = idx(rects[i].y2, ys);
        }
        sx = idx(sx, xs); sy = idx(sy, ys);
        dx = idx(dx, xs); dy = idx(dy, ys);

        // Reset the graph
        FOR(i, 0, xs.size() * ys.size()) {
            graph[i].clear();
            visited[i] = false;
        }

        // Connect adjancent points on rectangles
        FOR(i, 0, n) {
            FOR(x, rects[i].x1, rects[i].x2) for (int y : {rects[i].y1, rects[i].y2}) {
                graph[Node(x, y)].push_back(Node(x + 1, y));
                graph[Node(x + 1, y)].push_back(Node(x, y));
            }
            FOR(y, rects[i].y1, rects[i].y2) for (int x : {rects[i].x1, rects[i].x2}) {
                graph[Node(x, y)].push_back(Node(x, y + 1));
                graph[Node(x, y + 1)].push_back(Node(x, y));
            }
        }

        // Line sweep to connect points between different rectangles
        vector<pair<Node, int>> x_events;
        FOR(i, 0, n) {
            FOR(y, rects[i].y1, rects[i].y2 + 1) {
                x_events.push_back({{rects[i].x1, y}, 1});
                x_events.push_back({{rects[i].x2, y}, -1});
            }
        }
        sort(x_events.begin(), x_events.end(), cmp_x);
        int cnt = 0;
        FOR(i, 0, x_events.size()) {
            if (!cnt && i && x_events[i].first.y == x_events[i - 1].first.y) {
                graph[x_events[i].first].push_back(x_events[i - 1].first);
                graph[x_events[i - 1].first].push_back(x_events[i].first);
            }
            cnt += x_events[i].second;
        }

        vector<pair<Node, int>> y_events;
        FOR(i, 0, n) {
            FOR(x, rects[i].x1, rects[i].x2 + 1) {
                y_events.push_back({{x, rects[i].y1}, 1});
                y_events.push_back({{x, rects[i].y2}, -1});
            }
        }
        sort(y_events.begin(), y_events.end(), cmp_y);
        cnt = 0;
        FOR(i, 0, y_events.size()) {
            if (!cnt && i && y_events[i].first.x == y_events[i - 1].first.x) {
                graph[y_events[i].first].push_back(y_events[i - 1].first);
                graph[y_events[i - 1].first].push_back(y_events[i].first);
            }
            cnt += y_events[i].second;
        }

        // Dijkstra
        ll ans = dijkstra({sx, sy}, {dx, dy});
        if (~ans) cout << ans << '\n';
        else cout << "No Path\n";
    }
    return 0;
}