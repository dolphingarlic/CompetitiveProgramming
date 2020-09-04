#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
struct Point {
    ll x, y;
    int idx;
};

bool operator<(Point A, Point B) {
    if (A.x == B.x) return A.y < B.y;
    return A.x < B.x;
}
 
ostream& operator<<(ostream& out, Point P) {
    out << P.x << ' ' << P.y;
    return out;
}

struct Seg {
    Point p1, p2;
} s[100001];

ll curr_x;

bool operator<(Seg A, Seg B) {
    double yA, yB;
    if (A.p1.x == A.p2.x) yA = A.p1.y;
    else {
        double m = double(A.p2.y - A.p1.y) / (A.p2.x - A.p1.x);
        double c = A.p1.y - m * A.p1.x;
        yA = m * curr_x + c;
    }
    if (B.p1.x == B.p2.x) yB = B.p1.y;
    else {
        double m = double(B.p2.y - B.p1.y) / (B.p2.x - B.p1.x);
        double c = B.p1.y - m * B.p1.x;
        yB = m * curr_x + c;
    }
    return yA < yB;
}

bool operator==(Seg A, Seg B) {
    return A.p1.idx == B.p1.idx;
}

Point rightmost[100001];
vector<Point> events;
set<Seg> active;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i].p1.x >> s[i].p1.y >> s[i].p2.x >> s[i].p2.y;
        if (s[i].p2 < s[i].p1) swap(s[i].p1, s[i].p2);
        s[i].p1.idx = s[i].p2.idx = i;
        events.push_back(s[i].p1);
        events.push_back(s[i].p2);
    }
    sort(events.begin(), events.end());
    
    Point ninf = {INT_MIN, INT_MAX, n}, inf = {INT_MAX, INT_MAX, n};
    active.insert({ninf, inf}); // The "sentinel"
    rightmost[n] = {0, 0, -1};

    for (Point i : events) {
        curr_x = i.x;
        if (active.find(s[i.idx]) != active.end()) {
            // Right endpoint of segment
            active.erase(s[i.idx]);
            auto nxt = active.lower_bound(s[i.idx]);
            rightmost[nxt->p1.idx] = i;
        } else {
            // Left endpoint of segment
            auto nxt = active.lower_bound(s[i.idx]);
            if (rightmost[nxt->p1.idx].idx != -1) {
                cout << rightmost[nxt->p1.idx] << ' ' << i << '\n';
            }
            rightmost[i.idx] = rightmost[nxt->p1.idx] = i;
            active.insert(s[i.idx]);
        }
    }
    return 0;
}
