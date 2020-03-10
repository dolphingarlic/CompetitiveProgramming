#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Rational {
    ll whole, num, den;
    Rational(ll num = 0): whole(num), num(0), den(1) {}
    Rational(ll whole, ll num, ll den): whole(whole), num(num), den(den) {
        norm();
    }

    Rational(ll num, ll den): Rational(0, num, den) {}

    Rational& norm() {
        if (num > den) {
            whole += num / den;
            num %= den;
        }
        ll g = __gcd(num, den);
        num /= g;
        den /= g;
        return *this;
    }
};

bool operator<(const Rational& u, const Rational& v) {
    if (u.whole == v.whole) return u.num * v.den < u.den * v.num;
    return u.whole < v.whole;
}

ostream& operator<<(ostream& cout, const Rational& u) {
    return cout << u.whole * u.den + u.num << '/' << u.den;
}

ll y[2001], s[2001];
Rational intersect[2001][2001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("falling.in", "r", stdin);
    freopen("falling.out", "w", stdout);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) cin >> y[i];
    FOR(i, 1, n + 1) cin >> s[i];
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) {
        intersect[i][j] = Rational(1e9);
        if (i == j) continue;
        if ((j - i) * (y[j] - y[i]) > 0) intersect[i][j] = Rational(abs(y[j] - y[i]), abs(j - i));
    }
    FOR(i, 1, n + 1) {
        Rational ans = intersect[i][s[i]];
        FOR(j, 1, n + 1) {
            if (intersect[i][j] < intersect[j][s[i]] && intersect[j][s[i]] < Rational(1e9))
                ans = min(ans, intersect[j][s[i]]);
        }
        if (ans < Rational(1e9)) cout << ans << '\n';
        else cout << "-1\n";
    }
    return 0;
}