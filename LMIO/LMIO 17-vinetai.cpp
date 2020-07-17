#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, d;
bool visited[10];

void answer(int val) {
    if (~val) cout << val;
    else cout << "NESIDALO";
    exit(0);
}

void add_digit(int &rem, int &sum, int digit) {
    rem = rem * 10 + digit;
    sum += rem / d;
    rem %= d;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> d;
    if (n % m != 0) answer(-1);

    int groups = n / m, len = m - 1;
    if (d == 1) answer(groups);

    int sum = 0, rem = 1;
    FOR(i, 2, groups + 1) {
        FOR(j, 0, len) add_digit(rem, sum, 0);
        add_digit(rem, sum, 1);

        if (!rem) answer(groups % i ? -1 : sum * (groups / i));
        else if (visited[rem]) answer(-1);
        else visited[rem] = true;
    }

    answer(rem ? -1 : sum);
    return 0;
}