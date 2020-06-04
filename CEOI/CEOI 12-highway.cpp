/*
CEOI 2012 Highway
- First, we find a point P such that 0--P is the first highway
- While we do that, we also find all pairs (2 * i - 1, 2 * i)
  such that (0, 2 * i - 1, 2 * i) don't form a straight line
- Since the grader sucks, we can always find both in N/2 queries
- Next, we can simply check which of 2 * i - 1 or 2 * i lies on the
  second line for the first 2 pairs
    - We know there will always be at least 2 pairs because each
      highway has at least 3 points
- Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

#include "office.h"

int main() {
    int n = GetN();

    vector<int> same, different;
    for (int i = 2; i < n; i += 2) {
        if (isOnLine(1, i, i + 1)) same.push_back(i);
        else different.push_back(i);
    }
    if (same.size() && n % 2 == 0) {
        if (isOnLine(1, same[0], n)) same.push_back(n);
        else different.push_back(n);
    }

    int a2;
    if (isOnLine(1, same[0], different[0])) a2 = different[0] + 1;
    else a2 = different[0];

    int b2;
    if (isOnLine(1, same[0], different[1])) b2 = different[1] + 1;
    else b2 = different[1];

    Answer(1, same[0], a2, b2);
    return 0;
}