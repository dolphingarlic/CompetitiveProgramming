#include "books.h"
#include <math.h>
#include <algorithm>

long long minimum_walk(std::vector<int> p, int s) {
    int greatest = 0, n = p.size();
    long long dist = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] != i) {
            ans += abs(p[i] - i);
            if (i > greatest) dist += i - greatest;
            greatest = std::max(greatest, p[i]);
        }
    }
    return ans + 2 * dist;
}
