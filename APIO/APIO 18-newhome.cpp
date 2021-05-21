/*
APIO 2018 New Home
- Consider the case where all stores are always active
- We basically want the maximum of a bunch of "broken absolute value" graphs
- Consider the positive and negative slopes separately
- If we do this, then we get a bunch of line segments
- WLOG, extend the line segments into rays that go below the x-axis
- Since all slopes are equal, we only need to store the x-intersect of each ray
- Queries thus become prefix maximum queries (i.e. maximum ray that starts
  before the queried position)
- We can handle this using a simple segment tree
- To handle the general case, notice that there are O(N) possible rays, each
  with a period of relevance
- We can thus create a second segment tree indexed on time, where each leaf
  is a query, and DFS on that tree to update our first segment tree
- We can avoid an additional log N factor by keeping an array of sets that
  store "hidden" values at each point
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    return 0;
}
