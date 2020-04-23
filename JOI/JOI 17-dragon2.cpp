/*
JOI 2017 Dragon 2
- Smart method (i.e. not this method)
    - Notice how for each dragon, the other dragons it can attack and hit the road lie in
      an intersection of half planes
        - The half planes are (to the left/right of X--A) and (to the right/left of X--B)
    - This means we can sort all dragons by angles from A and sweep to maintain the first half plane
    - We don't have to explicitly maintain the second half plane
        - Sort the dragons in a separate list first by tribe and then by angle from B
        - Notice how if we use a BIT, we can efficiently count how many dragons in the
          first half plane are also in the second half plane
            - We can use something like std::lower_bound to help find the query indices
    - So sweep through the dragons sorted by A and for each dragon, update all its queries
    - This is slightly too slow, so we use sqrt decomposition
    - If a tribe has >500 queries where it's the attacker, then answer those queries from the defenders'
      perspective
        - The half-planes for this are slightly different but still manageable
    - This is very hard to implement though
    - Complexity: O(N sqrt(Q) log(N))
- Dumb brute force that somehow passes
    - Just check each pair of dragons in the query and see if it contributes to the answer
    - Analysis on why this works:
        - In the worst case, the sizes of the tribes we query are maximal
        - This means we can effectively assume there are only sqrt(Q) tribes, since smaller
          and unqueried tribes only improve the complexity
        - If we want the sum of the pairwise products of the sizes to be maximal, the sizes
          will all be around N/sqrt(Q)
        - Therefore, the complexity is only O(N^2), which is fast enough since N is small
    - Complexity: O(N^2)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point { ll x, y; } A, B;

bool ccw(Point X, Point Y, Point Z) { return (X.x - Y.x) * (Z.y - Y.y) <= (X.y - Y.y) * (Z.x - Y.x); }

vector<Point> by_t[30001];

int main() {
    int n, m, q, x, y;
    scanf("%d %d", &n, &m);
    while (n--) {
        scanf("%lld %lld %d", &A.x, &A.y, &q);
        by_t[q].push_back(A);
    }
    scanf("%lld %lld %lld %lld\n%d", &A.x, &A.y, &B.x, &B.y, &q);
    while (q--) {
        scanf("%d %d", &x, &y);
        m = 0;
        for (Point i : by_t[x]) for (Point j : by_t[y]) {
            if (ccw(i, A, B)) m += (ccw(i, A, j) & ccw(j, B, i));
            else m += (ccw(j, A, i) & ccw(i, B, j));
        }
        printf("%d\n", m);
    }
    return 0;
}