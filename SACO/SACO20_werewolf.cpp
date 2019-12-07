#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Component {
    priority_queue<ll> *pq;
    ll sm;
};
struct Query {
    int S, R, id;
    bool operator<(Query b) {
        return R < b.R;
    }
};

int cmp[200001];
int find(int a) {
    while (a != cmp[a]) cmp[a] = cmp[cmp[a]], a = cmp[a];
    return a;
}
void onion(int a, int b) {
    cmp[find(b)] = cmp[find(a)];
}

int N, M, Q, T;
ll V[200001];

Component area[200001];
Query queries[200001];
vector<int> graph[200001];
int ans[200001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> Q >> T;
    FOR(i, 0, N) {
        cin >> V[i];
        area[i].pq = new priority_queue<ll>();
        cmp[i] = i;
    }
    FOR(i, 0, M) {
        int X, Y;
        cin >> X >> Y;
        if (X < Y) swap(X, Y);
        graph[X].push_back(Y);
    }
    FOR(i, 0, Q) {
        cin >> queries[i].S >> queries[i].R;
        queries[i].id = i;
    }

    sort(queries, queries + Q);
    int ptr = 0;
    for (int i = 0; i < N && ptr < Q; i++) {
        int mx_size = 0, mx_child = -1;
        for (int j : graph[i]) {
            if (find(j) != i && area[find(j)].pq->size() > mx_size) {
                mx_child = j;
                mx_size = area[find(j)].pq->size();
            }
        }

        if (~mx_child) {
            area[i].pq = area[find(mx_child)].pq;
            area[i].sm = area[find(mx_child)].sm;
            onion(i, mx_child);
        }
        area[i].pq->push(V[i]);
        area[i].sm += V[i];

        for (int j : graph[i]) {
            if (find(j) != find(i)) {
                while (area[find(j)].pq->size()) {
                    int k = area[find(j)].pq->top();
                    area[find(j)].pq->pop();

                    area[i].pq->push(k);
                    area[i].sm += k;
                }
                onion(i, j);
            }
        }
        while (area[i].sm > T) {
            area[i].sm -= area[i].pq->top();
            area[i].pq->pop();
        }

        while (ptr < Q && queries[ptr].R == i) {
            ans[queries[ptr].id] = area[find(queries[ptr].S)].pq->size();
            ptr++;
        }
    }

    FOR(i, 0, Q) cout << ans[i] << '\n';
    return 0;
}