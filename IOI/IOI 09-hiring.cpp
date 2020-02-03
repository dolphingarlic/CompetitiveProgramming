#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Worker {
    int s, id;
    double ratio;
};
bool operator<(Worker A, Worker B) {
    if (A.s == B.s) return A.ratio < B.ratio;
    return A.s < B.s;
}
bool cmp(Worker A, Worker B) {
    if (A.ratio == B.ratio) return A.s < B.s;
    return A.ratio < B.ratio;
}

Worker workers[500001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll m;
    cin >> n >> m;
    FOR(i, 0, n) {
        int s, q;
        cin >> q >> s;
        workers[i] = {s, i + 1, (double)q / s};
    }
    sort(workers, workers + n, cmp);

    int best_pos = -1, mx_workers = 0;
    double best_pay = 1e18;

    priority_queue<Worker> pq;
    ll sm = 0;
    FOR(i, 0, n) {
        pq.push(workers[i]);
        sm += workers[i].s;
        while (sm * workers[i].ratio > m) {
            sm -= pq.top().s;
            pq.pop();
        }

        if (pq.size() > mx_workers) {
            mx_workers = pq.size();
            best_pay = sm * workers[i].ratio;
            best_pos = i;
        } else if (pq.size() == mx_workers && sm * workers[i].ratio < best_pay) {
            best_pay = sm * workers[i].ratio;
            best_pos = i;
        }
    }

    while (pq.size()) pq.pop();
    sm = 0;
    FOR(i, 0, n) {
        pq.push(workers[i]);
        sm += workers[i].s;
        while (sm * workers[i].ratio > m) {
            sm -= pq.top().s;
            pq.pop();
        }

        if (i == best_pos) {
            cout << mx_workers << '\n';
            while (pq.size()) {
                cout << pq.top().id << '\n';
                pq.pop();
            }
            return 0;
        }
    }
    return 0;
}