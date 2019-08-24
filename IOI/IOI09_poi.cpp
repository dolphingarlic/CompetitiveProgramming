#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
using namespace std;

#define MAX_N 2000
#define MAX_T 2000

vector<int> solved[MAX_N];
int points[MAX_T];
int score[MAX_N];

bool poiLess(int x, int y) {
    if (score[x] > score[y])
        return true;
    else if (score[x] == score[y]) {
        if (solved[x].size() > solved[y].size())
            return true;
        else if (solved[x].size() == solved[y].size())
            return x < y;
        else
            return false;
    } else
        return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, t, p;

    cin >> n >> t >> p;

    p--;

    memset(points, 0, sizeof(points));

    for (int i = 0; i < n; i++) {
        solved[i].reserve(n);
        int x;
        for (int j = 0; j < t; j++) {
            cin >> x;
            if (x == 1)
                solved[i].push_back(j);
            else
                points[j]++;
        }
    }

    vector<int> sortedIds;
    sortedIds.reserve(n);
    for (int i = 0; i < n; i++) {
        score[i] = 0;
        for (unsigned int j = 0; j < solved[i].size(); j++)
            score[i] += points[solved[i][j]];
        sortedIds.push_back(i);
    }

    sort(sortedIds.begin(), sortedIds.end(), poiLess);

    for (int i = 0; i < n; i++)
        if (sortedIds[i] == p) {
            cout << score[p] << ' ' << (i + 1) << '\n';
            return 0;
        }

    return 0;
}