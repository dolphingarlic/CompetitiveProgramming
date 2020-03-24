#include "Catherine.h"

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

namespace {

int A, B, last;
bool going_up;
vector<int> seen;
vector<vector<int>> good = {
    {1, 1, 0, 0, 1},
    {1, 0, 0, 1, 0},
    {0, 0, 1, 0, 1},
    {0, 1, 0, 1, 1},
    {1, 0, 1, 1, 0},
    {0, 1, 1, 0, 0},
};

int move_tree(vector<int> y) {
    vector<int> new_y = y;
    if (~last) new_y[last]++;

    int deg = accumulate(new_y.begin(), new_y.end(), 0);
    if (deg != 2) going_up = true;

    if (going_up) {
        if (deg == 1) {
            if (last == -1) FOR(i, 0, A) if (y[i]) return last = i;
            return -1;
        } else if (deg == 2) {
            FOR(i, 0, A) if (y[i]) return last = i;
        } else {
            FOR(i, 0, A) if (new_y[i] == 1) {
                if (!y[i]) return -1;
                return last = i;
            }
        }
    } else {
        if (~last) {
            FOR(i, 0, A) if (y[i]) {
                seen.push_back(i);
                if (seen.size() < 5) return last = i;
                else {
                    going_up = true;
                    for (vector<int> v : good)
                        if (v == seen) return last = i;
                    return -1;
                }
            }
        } else {
            FOR(i, 0, A) if (y[i]) {
                seen.push_back(i);
                y[i]--;
                FOR(j, 0, A) if (y[j]) {
                    seen.push_back(j);
                    return last = j;
                }
            }
        }
    }
}

int move_graph(vector<int> y) {
    if (~last) y[last]++;
    FOR(i, 0, 3) if (y[i] && y[(i + 1) % 3]) return last = i;
    FOR(i, 0, 3) if (y[i]) return last = i;
}

}  // namespace

void Init(int A, int B) {
    ::A = A;
    ::B = B;
    going_up = false;
    last = -1;
}

int Move(vector<int> y) {
    if (B) return move_tree(y);
    return move_graph(y);
}
