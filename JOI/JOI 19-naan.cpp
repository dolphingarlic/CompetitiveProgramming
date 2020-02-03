/*
JOI 2019 Naan
- We claim that it is always possible to find a fair split. We prove this with induction
    - Base case: It's always possible for 1 person
    - Assume that for a naan of tastiness X_i for person i, it's possible to split it
      amongst N-1 people fairly
    - Consider the points where we can cut the naan and satisfy person i. Take the leftmost point
        - Say this is for person A
    - If we cut it here and delete person A, then for each remaining person the tastiness X'_i satisfies
      X'_i / N-1 >= X_i / N
    - Therefore, by induction, this is true
    - This also provides us with a way to construct the answer
- We can just binary search and brute force from here, but that's ugly and precision is an issue
- Let the points where we split the naan for person i such that the left part has tastiness j * X_i / N
  be split[i][j]
    - Notice that split[i][j] < split[i][j + 1]
    - This means for the leftmost person i, for every other person k we have
      split[i][j] < split[k][j] < split[k][j + 1]
    - Notice how this means that we can just straight-up take split[k][j + 1] as the next split position
      and still make it fair
    - There's no more need for binsearch and this has no precision issues
- Complexity: O(N^2 log MAX_X) (log factor from GCD)
*/

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
    return cout << u.whole * u.den + u.num << ' ' << u.den;
}

Rational split[2001][2001];
bool visited[2001];
int order[2001];
ll a[2001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, l;
    cin >> n >> l;
    FOR(i, 0, n) {
        ll sm = 0;
        FOR(j, 0, l) {
            cin >> a[j];
            sm += a[j];
        }

        ll curr = 0;
        int idx = 0;
        FOR(j, 1, n) {
            while ((curr + a[idx]) * n <= sm * j) curr += a[idx++];
            ll res = sm * j - curr * n;
            split[i][j] = Rational(idx, res, n * a[idx]);
        }
    }

    FOR(i, 1, n) {
        Rational earliest = Rational(1000000000);
        FOR(j, 0, n) if (!visited[j] && split[j][i] < earliest) {
            earliest = split[j][i];
            order[i] = j;
        }
        cout << earliest << '\n';
        visited[order[i]] = true;
    }
    FOR(i, 0, n) if (!visited[i]) order[n] = i;
    FOR(i, 1, n + 1) cout << order[i] + 1 << ' ';
    return 0;
}