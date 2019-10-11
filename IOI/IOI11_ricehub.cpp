#include <algorithm>
#include "ricehub.h"
typedef long long ll;

ll all[100005];

int besthub(int R, int L, int X[], long long B) {
    for (int i = 1; i <= R; i++) all[i] = X[i - 1];
    std::sort(all + 1, all + R + 1);
    ll left = 1, right = 1, mx = -1, totalSum = 0;
    ll median = 1, newmedian;
    ll cost = 0;
    ll mxInterval = -1;
    while (right <= R) {
        totalSum += all[right];
        int range = (right - left + 1);
        newmedian = (left + right) >> 1;
        cost += all[right] - all[median];
        if (newmedian > median) {
            while (median < newmedian) {
                int change = median - left + 1 - (right - median);
                cost += 1ll * change * (all[median + 1] - all[median]);
                median++;
            }
        }
        while (cost > B) {
            left++;
            cost -= all[median] - all[left - 1];
            while (median < ((left + right) >> 1)) {
                int change = median - left + 1 - (right - median);
                cost += 1ll * change * (all[median + 1] - all[median]);
                median++;
            }
        }
        mxInterval = std::max(mxInterval, right - left + 1);
        right++;
    }
    return mxInterval;
}