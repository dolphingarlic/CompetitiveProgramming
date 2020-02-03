// #include "creclib.h"
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void play() {
    while (true) {
        ll x = dimension_x(), y = dimension_y();
        if (x > y) {
            int l = 0, r = 32;
            while (l != r) {
                int mid = (l + r + 1) / 2;
                if ((1 << mid) * (y + 1) - 1 < x) l = mid;
                else r = mid - 1;
            }
            cut(vertical, (1 << l) * (y + 1) - 1);
        } else {
            int l = 0, r = 32;
            while (l != r) {
                int mid = (l + r + 1) / 2;
                if ((1 << mid) * (x + 1) - 1 < y) l = mid;
                else r = mid - 1;
            }
            cut(horizontal, (1 << l) * (x + 1) - 1);
        }
    }
    return 0;
}