/*
IOI 2020 Carnival Tickets
- Since N is even, the score from each round is (sum of greater half) - (sum of lesser half)
- Assign each ticket a + or a - that denotes which sum it'll contribute toward
- We can start off with each colour's K smallest tickets having -s, and then using a priority
  queue to greedily turn them into +s until we have NK/2 +s and -s
- Notice how the smallest ticket with a + is larger than the largest ticket with a -
- We can then construct the answer for each round like so:
    - Sort the colours by their remaining number of +s
    - Pick +s from the top half of this list
    - Pick -s from the bottom half of this list
- We can use a priority queue to speed this up
- Complexity: O(NK log N)
*/

#include "tickets.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll find_maximum(int k, vector<vector<int>> x) {
    int n = x.size();
    int m = x[0].size();

    vector<vector<int>> le(n), gr(n);
    vector<int> lcnt(n, k), gcnt(n);
    priority_queue<pair<int, int>> pq;
    ll val = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            le[i].push_back(x[i][j]);
            val -= x[i][j];
        }
        pq.push({x[i][m - 1] + x[i][k - 1], i});
    }
    for (int _ = 0; _ < n * k / 2; _++) {
        val += pq.top().first;
        int i = pq.top().second;
        pq.pop();
        le[i].pop_back();
        gr[i].push_back(x[i][m - gcnt[i] - 1]);
        lcnt[i]--, gcnt[i]++;
        if (lcnt[i]) pq.push({x[i][m - gcnt[i] - 1] + x[i][lcnt[i] - 1], i});
    }

    vector<vector<int>> alloc(n, vector<int>(m, -1));
    while (pq.size()) pq.pop();
    for (int i = 0; i < n; i++) pq.push({gcnt[i], i});
    for (int i = 0; i < k; i++) {
        vector<bool> used(n);
        for (int j = 0; j < n / 2; j++) {
            int idx = pq.top().second;
            pq.pop();
            alloc[idx][m - gcnt[idx] + gr[idx].size() - 1] = i;
            gr[idx].pop_back();
            used[idx] = true;
        }
        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                alloc[j][le[j].size() - 1] = i;
                le[j].pop_back();
            } else pq.push({gr[j].size(), j});
        }
    }

    allocate_tickets(alloc);
    return val;
}
