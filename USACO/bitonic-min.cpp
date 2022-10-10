#include "bitonic_main.h"
#include <map>
#include <utility>
using namespace std;

int N;

void init(int S, int _N) { N = _N; }

map<pair<int, int>, int> cache;

bool query(int x, int y) {
    if (cache.count({x, y})) return cache[{x, y}];
    if (cache.count({y, x})) return !cache[{y, x}];
    return cache[{x, y}] = less_than(x, y);
}

int solve() {
    cache.clear();
    int l = 0, r = N - 1;
    while (l != r) {
        int mid = (l + r) / 2;

    }
}
