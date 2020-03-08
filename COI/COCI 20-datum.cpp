/*
COCI 2020 Datum
- Ew
- Just do it
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
struct Date {
    int d, m, y, t;
};
 
bool operator<(Date A, Date B) {
    if (A.y == B.y) {
        if (A.m == B.m) {
            if (A.d == B.d) return A.t < B.t;
            return A.d < B.d;
        }
        return A.m < B.m;
    }
    return A.y < B.y;
}
 
int lim[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
vector<Date> palindromes;
 
int main() {
    FOR(i, 0, 4) FOR(j, 0, 10) FOR(k, 0, 2) FOR(l, 0, 10) {
        if (10 * k + l > 0 && 10 * k + l < 13 && 10 * i + j > 0 && 10 * i + j <= lim[10 * k + l - 1] + ((10 * j + i) % 4 == 0 && 10 * k + l == 2))
            palindromes.push_back({10 * i + j, 10 * k + l, 1000 * l + 100 * k + 10 * j + i, 0});
    }
    sort(palindromes.begin(), palindromes.end());
 
    int n;
    scanf("%d", &n);
    while (n--) {
        Date q;
        scanf("%2d.%2d.%4d.", &q.d, &q.m, &q.y);
        Date nxt = *upper_bound(palindromes.begin(), palindromes.end(), q);
        printf("%02d.%02d.%04d.\n", nxt.d, nxt.m, nxt.y);
    }
    return 0;
}