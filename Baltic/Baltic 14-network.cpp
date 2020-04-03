/*
Baltic 2014 Network
- First, ping all computers with B
- If A->B goes A->C->B, then A->C == A->B - C->B - 1
- Just do it
*/

#include "network.h"
#include <vector>

int dist[1001];
std::vector<int> from_b[1001];

void findRoute(int N, int a, int b) {
    for (int i = 1; i <= N; i++) {
        if (i == b) continue;
        dist[i] = ping(i, b);
        from_b[dist[i]].push_back(i);
    }

    for (int i = dist[a]; i; i--) {
        for (int j : from_b[i - 1]) if (!ping(a, j)) {
            travelTo(j);
            a = j;
            break;
        }
    }
    travelTo(b);
}
