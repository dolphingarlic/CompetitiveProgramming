/*
CEOI 2011 Balloons
- Notice how if balloon A comes after balloon B and A's radius > B's radius, no balloon
  after A touches B
- This means we can just use a monotone stack to keep track of "important balloons"
- Use Pythagoras to find a formula for the distance between centers if 2 balloons touch
- Complexity: O(N)
*/

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
        printf("%.4lf\n", r);
    }
    return 0;
}