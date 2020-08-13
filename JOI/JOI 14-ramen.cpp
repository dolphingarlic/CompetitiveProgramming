/*
JOI 2014 Ramen
- 2N queries: Keep a running lo/hi and update it for every element
- 1.5N queries: Instead of comparing each element with lo/hi, compare
                it with its neighbour and compare the lower/greater
				with lo/hi accordingly
*/

#include "ramen.h"

void Ramen(int N) {
    int lo = -1, hi = -1;
    if (N & 1) lo = hi = N - 1;
    for (int i = 0; i < N - 1; i += 2) {
        if (~Compare(i, i + 1)) {
            if (hi == -1 || ~Compare(i, hi)) hi = i;
            if (lo == -1 || ~Compare(lo, i + 1)) lo = i + 1;
        } else {
            if (hi == -1 || ~Compare(i + 1, hi)) hi = i + 1;
            if (lo == -1 || ~Compare(lo, i)) lo = i;
        }
    }
    Answer(lo, hi);
}
