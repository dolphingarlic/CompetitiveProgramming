#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Point {
    int x, y, id;

    bool operator<(Point b) {
        if (x == b.x) return y < b.y;
        return x < b.x;
    }
};

Point rec[100002];
int intended[100002], res[100002], ans[100002];

bool interfere(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) <= 100;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> rec[i].x >> rec[i].y;
        rec[i].id = i;
    }
    FOR(i, 1, n + 1) cin >> intended[i];
    sort(rec + 1, rec + n + 1);
    rec[0] = {rec[1].x - 100, rec[1].y - 100, 0}, rec[n + 1] = {rec[n].x + 100, rec[n].y + 100, n + 1};

    FOR(i, 1, n + 1) {
        res[i - 1] = res[i + 1] = 0;

        res[i] = 0;
        for (int j = i + 1; j <= n && interfere(rec[j - 1], rec[j]); j++) {
            res[j] = intended[rec[j - 1].id] ^ res[j - 1] ^ res[j - 2];
            res[j + 1] = 0;
        }
        bool correct = (res[i] ^ res[i + 1] == intended[rec[i].id]);
        for (int j = i + 1; j <= n && interfere(rec[j - 1], rec[j]); j++) {
            correct &= (res[j] ^ res[j - 1] ^ res[j + 1] == intended[rec[j].id]);
        }
        if (correct) {
            ans[rec[i].id] = res[i];
            for (i++; i <= n && interfere(rec[i - 1], rec[i]); i++) {
                ans[rec[i].id] = res[i];
            }
            i--;
            continue;
        }

        res[i] = 1;
        for (int j = i + 1; j <= n && interfere(rec[j - 1], rec[j]); j++) {
            res[j] = intended[rec[j - 1].id] ^ res[j - 1] ^ res[j - 2];
            res[j + 1] = 0;
        }
        correct = (res[i] ^ res[i + 1] == intended[rec[i].id]);
        for (int j = i + 1; j <= n && interfere(rec[j - 1], rec[j]); j++) {
            correct &= (res[j] ^ res[j - 1] ^ res[j + 1] == intended[rec[j].id]);
        }
        if (correct) {
            ans[rec[i].id] = res[i];
            for (i++; i <= n && interfere(rec[i - 1], rec[i]); i++) {
                ans[rec[i].id] = res[i];
            }
            i--;
            continue;
        }

        return cout << -1, 0;
    }

    FOR(i, 1, n + 1) cout << ans[i] << ' ';
    return 0;
}