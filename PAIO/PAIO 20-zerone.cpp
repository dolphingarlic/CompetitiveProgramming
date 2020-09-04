#include <bits/stdc++.h>
using namespace std;

inline int query(int a, int b) {
    cout << a << ' ' << b << endl;
    int g;
    cin >> g;
    return g;
}

void ans(int p) {
    cout << "! " << p << endl;
    string s;
    cin >> s;
    if (s == "NOK") exit(0);
}

int find_zero(int n) {
    if (n == 3) return -1;

    int curr = 1;
    vector<int> cand(n - 1);
    iota(cand.begin(), cand.end(), 2);
    while (1) {
        map<int, vector<int>> cnt;
        int mx = 0;
        for (int i : cand) {
            int g = query(curr, i);
            mx = max(mx, g);
            cnt[g].push_back(i);
        }
        cand = cnt[mx];
        if (cand.size() == 1) {
            cnt.clear();
            for (int i = 1; i <= n; i++) {
                if (i == curr) continue;
                cnt[query(curr, i)].push_back(i);
            }
            if (cnt.size() == n - 1) return curr;
            return cand.back();
        }
        curr = cand.back();
        cand.pop_back();
    }
}

int find_one(int n) {
    map<int, vector<int>> cnt;
    int mx = 0;
    for (int i = 2; i <= n; i++) {
        int g = query(1, i);
        mx = max(mx, g);
        cnt[g].push_back(i);
    }
    if (mx == 1) return 1;
    vector<int> s1 = cnt[1], s2 = cnt[mx];

    int zero;
    bool found = false;
    if (cnt.size() == n - 1) {
        zero = 1;
        found = true;
    } else if (s2.size() == 1) {
        zero = s2[0];
        found = true;
    }
    while (!found) {
        int curr = s2.back();
        s2.pop_back();
        cnt.clear();
        mx = 0;
        for (int i : s2) {
            int g = query(curr, i);
            mx = max(mx, g);
            cnt[g].push_back(i);
        }
        s2 = cnt[mx];
        if (s2.size() == 1) {
            int g1 = query(curr, s1[0]), g2 = query(s2[0], s1[0]);
            for (int i = 1; g1 == g2; i++) {
                if (g1 == 1) return s1[i - 1];
                g1 = query(curr, s1[i]), g2 = query(s2[0], s1[i]);
            }
            if (g1 > g2) zero = curr;
            else zero = s2[0];
            found = true;
        }
    }

    for (int i : s1) if (query(zero, i) == 1) return i;
    return -1;
}

int main() {
    int n;
    while (1) {
        cin >> n;
        if (n == -1) break;
        bool x;
        cin >> x;
        if (x) ans(find_one(n));
        else ans(find_zero(n));        
    }
    return 0;
}