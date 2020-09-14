/*
IOI 2020 Gift
- First, split the segments into x[i] = 1 and x[i] = 2
- Merge all x[i] = 1 segments that overlap and kinda squish them into 1 square
    - Then colour the bracelet alternating RBRBRB...
- Finally, check whether this satisfies all the x[i] = 2 segments
    - Such a segment is bad iff a[i] = b[i] or [a[i], b[i]] is a subsegment of some
      union of the x[i] = 1 segments
- Complexity: O(N log N)
*/

#include "gift.h"

#include <bits/stdc++.h>
using namespace std;

int construct(int n, int r, vector<int> a, vector<int> b, vector<int> x) {
    vector<pair<int, int>> sing, doub, itv;
    for (int i = 0; i < r; i++) {
        if (x[i] == 1) sing.push_back({a[i], b[i]});
        else doub.push_back({a[i], b[i]});
    }
    sort(sing.begin(), sing.end());
    pair<int, int> curr = {-1, -1};
    for (pair<int, int> i : sing) {
        if (i.first > curr.second) {
            itv.push_back(curr);
            curr = i;
        } else curr.second = max(curr.second, i.second);
    }
    itv.push_back(curr);
    sort(doub.begin(), doub.end());
    int s_ptr = 1;
    for (pair<int, int> i : doub) {
        while (s_ptr < itv.size() - 1 && itv[s_ptr].second < i.first)
            s_ptr++;
        if (i.first == i.second || (i.first >= itv[s_ptr].first && i.second <= itv[s_ptr].second))
            return 0;
    }

    string ret(n, '.');
    char c = 'R';
    for (int i = 1; i < itv.size(); i++) {
        for (int j = itv[i - 1].second + 1; j < itv[i].first; j++) {
            ret[j] = c;
            c = 'R' + 'B' - c;
        }
        for (int j = itv[i].first; j <= itv[i].second; j++)
            ret[j] = c;
        c = 'R' + 'B' - c;
    }
    for (int j = itv.back().second + 1; j < n; j++) {
        ret[j] = c;
        c = 'R' + 'B' - c;
    }
    craft(ret);
    return 1;
}
