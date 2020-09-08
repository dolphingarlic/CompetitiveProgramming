#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

array<int, 3> rbn[1001], hal[1001];
int len[2002], cnt[2002][3003];
pair<int, int> corresp[2002][3003];

pair<int, int> intersect(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        if (a.second == b.second) return a;
        return {a.first, 0};
    } else if (a.first == b.second) return {a.first, 0};
    else if (a.second == b.first) return {a.second, 0};
    else if (a.second == b.second) return {a.second, 0};
    return {0, 0};
}

bool bad(int idx, array<int, 3> a, array<int, 3> b) {
    if (!intersect(corresp[idx][a[0]], {b[0], 0}).first) return true;
    if (!intersect(corresp[idx][b[0]], {a[0], 0}).first) return true;

    // Check others
    
    return false;
}

void del_line(int idx, array<int, 3> a, array<int, 3> b) {
    for (int i = 0; i < 3; i++) {
        cnt[idx][a[i]]--;
        cnt[idx][b[i]]--;
    }

    // Change corresp
}

void add_line(int idx, array<int, 3> a, array<int, 3> b) {
    corresp[idx][a[0]] = {b[0], 0};
    corresp[idx][b[0]] = {a[0], 0};

    if (!cnt[idx][a[1]]) corresp[idx][a[1]] = {b[1], b[2]};
    if (!cnt[idx][a[2]]) corresp[idx][a[2]] = {b[1], b[2]};
    pair<int, int> ia1 = intersect(corresp[idx][a[1]], {b[1], b[2]});
    pair<int, int> ia2 = intersect(corresp[idx][a[2]], {b[1], b[2]});
    if (ia1.second) {
        if (ia2.second) corresp[idx][a[1]] = corresp[idx][a[2]] = ia1;
        else {
            corresp[idx][a[2]] = ia2;
            if (ia2.first == b[1]) corresp[idx][a[1]] = {b[2], 0};
            else corresp[idx][a[1]] = {b[1], 0};
        }
    } else {
        corresp[idx][a[1]] = ia1;
        if (ia1.first == b[1]) corresp[idx][a[2]] = {b[2], 0};
        else corresp[idx][a[2]] = {b[1], 0};
    }

    if (!cnt[idx][b[1]]) corresp[idx][b[1]] = {a[1], a[2]};
    if (!cnt[idx][b[2]]) corresp[idx][b[2]] = {a[1], a[2]};
    pair<int, int> ib1 = intersect(corresp[idx][b[1]], {a[1], a[2]});
    pair<int, int> ib2 = intersect(corresp[idx][b[2]], {a[1], a[2]});
    if (ib1.second) {
        if (ib2.second) corresp[idx][b[1]] = corresp[idx][b[2]] = ib1;
        else {
            corresp[idx][b[2]] = ib2;
            if (ib2.first == a[1]) corresp[idx][b[1]] = {a[2], 0};
            else corresp[idx][b[1]] = {a[1], 0};
        }
    } else {
        corresp[idx][b[1]] = ib1;
        if (ib1.first == a[1]) corresp[idx][b[2]] = {a[2], 0};
        else corresp[idx][b[2]] = {a[1], 0};
    }

    for (int i = 0; i < 3; i++) {
        cnt[idx][a[i]]++;
        cnt[idx][b[i]]++;
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    map<string, int> hsh;
    for (int i = 1, cnt = 1; i <= n; i++) {
        string a, b, c, t;
        cin >> a >> t >> b >> t >> c;
        if (!hsh.count(a)) hsh[a] = cnt++;
        if (!hsh.count(b)) hsh[b] = cnt++;
        if (!hsh.count(c)) hsh[c] = cnt++;
        rbn[i] = {hsh[a], hsh[b], hsh[c]};
        if (hsh[b] > hsh[c]) swap(rbn[i][1], rbn[i][2]);
    }
    hsh.clear();
    for (int i = 1, cnt = 1; i <= m; i++) {
        string a, b, c, t;
        cin >> a >> t >> b >> t >> c;
        if (!hsh.count(a)) hsh[a] = cnt++;
        if (!hsh.count(b)) hsh[b] = cnt++;
        if (!hsh.count(c)) hsh[c] = cnt++;
        hal[i] = {hsh[a], hsh[b], hsh[c]};
        if (hsh[b] > hsh[c]) swap(hal[i][1], hal[i][2]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int idx = j - i + n;
            while (bad(idx, rbn[i], hal[j])) {
                del_line(idx, rbn[i - len[idx]], hal[i - len[idx]]);
                len[idx]--;
            }
            add_line(idx, rbn[i], hal[j]);
            len[idx]++;
            ans = max(ans, len[idx]);
        }
    }
    cout << ans;
    return 0;
}