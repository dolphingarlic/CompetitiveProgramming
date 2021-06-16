/*
Baltic 2021 The Collection Game
- This is a buffed version of COI '21 MalnaRISC, so see that solution too
- We basically want to sort the artworks by swapping them in parallel
- https://en.wikipedia.org/wiki/Bitonic_sorter
- https://en.wikipedia.org/wiki/Batcher_odd%E2%80%93even_mergesort
- When a comparison returns 1, don't do anything because they've been sorted/swapped
- When a comparison returns 0, manually swap the two artworks in the answer array
- O(log^2 N) visits
*/

#include "swaps.h"

#include <numeric>
#include <algorithm>

void solve(int N, int V) {
    std::vector<int> ans(N);
    std::iota(ans.begin(), ans.end(), 1);
    int P2 = 1;
    while (P2 < N) P2 <<= 1;
    for (int P = 1; P < P2; P <<= 1)
        for (int k = P; k; k >>= 1) {
            std::vector<std::pair<int, int>> visited;
            for (int j = k % P; j < P2 - k; j += 2 * k)
                for (int i = 0; i < k && i + j + k < N; i++)
                    if ((i + j) / (2 * P) == (i + j + k) / (2 * P)) {
                        schedule(ans[i + j], ans[i + j + k]);
                        visited.push_back({i + j, i + j + k});
                    }
            std::vector<int> visit_res = visit();
            for (int i = 0; i < visit_res.size(); i++)
                if (!visit_res[i])
                    std::swap(ans[visited[i].first], ans[visited[i].second]);
        }
    answer(ans);
}