#include <bits/stdc++.h>
using namespace std;

stack<pair<double, double>> stck;

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        double x, r;
        scanf("%lf %lf", &x, &r);
        while (stck.size()) {
            r = min(r, (x - stck.top().first) * (x - stck.top().first) / stck.top().second / 4);
            if (r > stck.top().second) stck.pop();
            else break;
        }
        stck.push({x, r});
        printf("%.3lf\n", r);
    }
    return 0;
}