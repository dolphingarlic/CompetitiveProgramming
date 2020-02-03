#include "bubblesort2.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int INF = INT_MAX / 2;

int N, S;
int segtree[4000000], lazy[4000000];

void push_lazy(int node, int l, int r) {
	segtree[node] += lazy[node];
	if (l != r) {
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}
	lazy[node] = 0;
}

int query(int node) {
	return segtree[node] + lazy[node];
}
void update(int a, int b, int val, int node = 1, int l = 0, int r = S) {
	if (a == b || a >= r || b <= l) return;
	if (a <= l && b >= r) {
		lazy[node] += val;
		return;
	}
	push_lazy(node, l, r);

	int mid = (l + r) / 2;
	update(a, b, val, node * 2, l, mid);
	update(a, b, val, node * 2 + 1, mid, r);
	segtree[node] = max(query(node * 2), query(node * 2 + 1));
}

vector<int> countScans(vector<int> A, vector<int> X, vector<int> V) {
    int Q = X.size();
	N = A.size();
    vector<int> answer(Q);

	vector<pair<int, int>> compressed;
	FOR(i, 0, N) compressed.push_back({A[i], i});
	FOR(i, 0, Q) compressed.push_back({V[i], X[i]});
	sort(compressed.begin(), compressed.end());
	compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());

	const auto insert = [&](int a, int b) {
		int pos = lower_bound(compressed.begin(), compressed.end(), make_pair(a, b)) - compressed.begin();
		update(pos, pos + 1, INF + b);
		update(pos + 1, S, -1);
	};
	const auto erase = [&](int a, int b) {
		int pos = lower_bound(compressed.begin(), compressed.end(), make_pair(a, b)) - compressed.begin();
		update(pos, pos + 1, -(INF + b));
		update(pos + 1, S, 1);
	};

	S = compressed.size();
	update(0, S, -INF);
	FOR(i, 0, N) insert(A[i], i);

    FOR(i, 0, Q) {
		erase(A[X[i]], X[i]);
		insert(V[i], X[i]);
		A[X[i]] = V[i];
		
		answer[i] = query(1);
    }

    return answer;
}
