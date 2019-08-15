#include <queue>
#include "shoes.h"

int n;
long long bit[200001];
std::queue<int> left[100001], right[100001];

void update(int pos) {
    for (int i = pos; i <= n; i += (i & (-i))) bit[i]++;
}
long long query(int l, int r) {
    long long ans = 0;
    for (int i = r; i > 0; i -= (i & (-i))) ans += bit[i];
    for (int i = l; i > 0; i -= (i & (-i))) ans -= bit[i];
    return ans;
}

long long count_swaps(std::vector<int> s) {
    n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] < 0)
            left[-s[i]].push(i + 1);
        else
            right[s[i]].push(i + 1);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] < 0) {
            if (left[-s[i]].front() == i + 1) {
                int r_indx = right[-s[i]].front();
                right[-s[i]].pop();
                left[-s[i]].pop();

                ans += r_indx - i - 2 - query(i + 1, r_indx);
                update(r_indx);
            }
        } else {
            if (right[s[i]].front() == i + 1) {
                int l_indx = left[s[i]].front();
                right[s[i]].pop();
                left[s[i]].pop();

                ans += l_indx - i - 1 - query(i + 1, l_indx);
                update(l_indx);
            }
        }
    }
    return ans;
}