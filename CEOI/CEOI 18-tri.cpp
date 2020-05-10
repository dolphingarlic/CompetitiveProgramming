/*
CEOI 2018 Triangles
- First, split the points into 2 categories based on which side of the line 1--2 they're on
- We can then sort each side by their angle from point 1 and get the convex hull using the Graham scan
- Notice how these 2 convex hulls have a common edge 1--2
- Since the union of the 2 convex hulls might be concave at points 1 or 2, we can simply "relax" the
  concave stuff by deleting middle vertices until everything is convex
- Complexity: O(N log N)
*/

#include "trilib.h"

#include <bits/stdc++.h>
using namespace std;

bool cmp(int A, int B) { return is_clockwise(1, A, B); }

vector<int> divi[2]{{2}, {2}}, hull[2];

int main() {
    int n = get_n();
    for (int i = 3; i <= n; i++) divi[is_clockwise(1, 2, i)].push_back(i);

    for (int i = 0; i < 2; i++) {
        sort(divi[i].begin(), divi[i].end(), cmp);
        for (int j : divi[i]) {
            while (hull[i].size() > 1 && is_clockwise(j, hull[i].back(), hull[i][hull[i].size() - 2]))
                hull[i].pop_back();
            hull[i].push_back(j);
        }
        if (i) reverse(hull[i].begin(), hull[i].end());
        hull[i].insert(hull[i].begin(), 1);
    }

    if (min(hull[0].size(), hull[1].size()) == 2)
        return give_answer(max(hull[0].size(), hull[1].size())), 0;

    for (int i = 0; i < 2; i++) {
        hull[0].pop_back();

        while (true) {
            if (hull[0].size() > 1 && is_clockwise(hull[1].back(), hull[0].back(), hull[0][hull[0].size() - 2]))
                hull[0].pop_back();
            else if (hull[1].size() > 1 && is_clockwise(hull[1][hull[1].size() - 2], hull[1].back(), hull[0].back()))
                hull[1].pop_back();
            else break;
        }

        swap(hull[0], hull[1]);
        reverse(hull[0].begin(), hull[0].end());
        reverse(hull[1].begin(), hull[1].end());
    }

    give_answer(hull[0].size() + hull[1].size());
    return 0;
}