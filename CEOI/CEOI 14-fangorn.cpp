/*
CEOI 2014 Fangorn
- For two tree A and B, let A' be the reflection of A over B
    - Gimli can't cross the ray B->A'
- For each "center" tree, the plan gets split into T - 1 sectors
- Yeet each camp that isn't in the same sector as Gimli
- Complexity: O(C(N + C) log (N + C)) (plus some constant optimization)
*/


#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
    int x, y, id;
} trees[2001], camps[10001], gimli, pivot;

Point operator-(Point A, Point B) { return {A.x - B.x, A.y - B.y, A.id}; }

bool operator<(Point A, Point B) {
    return copysign(1. - A.x / (fabs(A.x) + fabs(A.y)), A.y) <
           copysign(1. - B.x / (fabs(B.x) + fabs(B.y)), B.y);
}

bool good[10001];
deque<Point> sweep;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int h, w;
    cin >> h >> w;
    cin >> gimli.x >> gimli.y;
    gimli.id = -1;
    int c;
    cin >> c;
    for (int i = 1; i <= c; i++) {
        cin >> camps[i].x >> camps[i].y;
        camps[i].id = i;
        good[i] = true;
    }
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) cin >> trees[i].x >> trees[i].y;
    srand(69420);
    random_shuffle(trees + 1, trees + t + 1);

    for (int i = 1; i <= t; i++) {
        pivot = trees[i];
        sweep.clear();
        sweep.push_back(gimli - pivot);
        for (int j = 1; j <= c; j++)
            if (good[j]) {
                good[j] = false;
                sweep.push_back(camps[j] - pivot);
            }
        for (int j = 1; j <= t; j++)
            if (i != j) sweep.push_back(pivot - trees[j]);
        sort(sweep.begin(), sweep.end());
        while (~sweep.front().id) {
            sweep.push_back(sweep.front());
            sweep.pop_front();
        }
        sweep.pop_front();
        for (Point j : sweep) {
            if (!j.id) break;
            good[j.id] = true;
        }
        reverse(sweep.begin(), sweep.end());
        for (Point j : sweep) {
            if (!j.id) break;
            good[j.id] = true;
        }
        if (accumulate(good + 1, good + c + 1, 0) > 5000) i++;
    }

    cout << accumulate(good + 1, good + c + 1, 0) << '\n';
    for (int i = 1; i <= c; i++)
        if (good[i]) cout << i << ' ';
    return 0;
}