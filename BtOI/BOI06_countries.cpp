#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Country {
    int x, y, s, id;
};
bool operator<(Country A, Country B) {
    if (A.s == B.s) return A.id < B.id;
    return A.s > B.s;
};

int cmp[1000];
int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(int A, int B) {
    cmp[find(A)] = cmp[find(B)];
}

Country c[1000];
string ans[1000];

double dist(Country A, Country B) {
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        cin >> c[i].x >> c[i].y >> c[i].s;
        c[i].id = i;
        cmp[i] = i;
    }
    sort(c, c + n);

    FOR(i, 0, n) {
        vector<pair<double, int>> v;
        FOR(j, 0, i) {
            double inf = c[j].s / dist(c[i], c[j]);
            if (inf > c[i].s) v.push_back({-inf, c[j].id});
        }
        sort(v.begin(), v.end());

        if (v.size()) {
            if (v.size() > 1 && v[0].first == v[1].first) ans[c[i].id] = "D";
            else {
                ans[c[i].id] = to_string(find(v[0].second) + 1);
                onion(c[i].id, v[0].second);
            }
        } else ans[c[i].id] = "K";
    }

    FOR(i, 0, n) cout << ans[i] << '\n';
    return 0;
}