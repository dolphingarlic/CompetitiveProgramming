#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

const int MAXN = 500001;

int n, x[MAXN], y[MAXN];
double pref_logs[MAXN];

pair<double, int> mx[4 * MAXN];
double lazy_mx[4 * MAXN];

ll prods[4 * MAXN];

void push_lazy_mx(int l, int r, int node) {
	mx[node].first += lazy_mx[node];
	if (l != r) {
		lazy_mx[node * 2] += lazy_mx[node];
		lazy_mx[node * 2 + 1] += lazy_mx[node];
	}
	lazy_mx[node] = 0;
}

void build(int l = 1, int r = n, int node = 1) {
	if (l == r) {
		mx[node] = {pref_logs[l] + log(y[l]), l};
		prods[node] = x[l];
	} else {
		int mid = (l + r) / 2;
		build(l, mid, node * 2);
		build(mid + 1, r, node * 2 + 1);

		mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
		prods[node] = (prods[node * 2] * prods[node * 2 + 1]) % MOD;
	}
}
void update_mx(int a, int b, double val, int l = 1, int r = n, int node = 1) {
	if (lazy_mx[node] != 0) push_lazy_mx(l, r, node);

	if (l > b || r < a) return;
	if (l >= a && r <= b) {
		lazy_mx[node] = val;
		push_lazy_mx(l, r, node);
	} else {
		int mid = (l + r) / 2;
		update_mx(a, b, val, l, mid, node * 2);
		update_mx(a, b, val, mid + 1, r, node * 2 + 1);

		mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
	}
}
void update_prod(int pos, ll val, int l = 1, int r = n, int node = 1) {
	if (l == r) prods[node] = val;
	else {
		int mid = (l + r) / 2;
		if (pos > mid) update_prod(pos, val, mid + 1, r, node * 2 + 1);
		else update_prod(pos, val, l, mid, node * 2);

		prods[node] = (prods[node * 2] * prods[node * 2 + 1]) % MOD;
	}
}
int query_mx() { return mx[1].second; }
ll query_prod(int pos, int l = 1, int r = n, int node = 1) {
	if (l > pos) return 1;
	if (r <= pos) return prods[node];
	int mid = (l + r) / 2;
	return (query_prod(pos, l, mid, node * 2) * query_prod(pos, mid + 1, r, node * 2 + 1)) % MOD;
}

int init(int N, int X[], int Y[]) {
	n = N;
	FOR(i, 0, n) x[i + 1] = X[i], y[i + 1] = Y[i];

	FOR(i, 1, n + 1) pref_logs[i] = pref_logs[i - 1] + log(x[i]);
	build();

	int best = query_mx();
	return (query_prod(best) * y[best]) % MOD;
}

int updateX(int pos, int val) {
	pos++;

	double mx_up = log(val) - log(x[pos]);

	x[pos] = val;

	update_mx(pos, n, mx_up);
	update_prod(pos, val);

	int best = query_mx();
	return (query_prod(best) * y[best]) % MOD;
}

int updateY(int pos, int val) {
	pos++;

	double mx_up = log(val) - log(y[pos]);
	
	y[pos] = val;

	update_mx(pos, pos, mx_up);

	int best = query_mx();
	return (query_prod(best) * y[best]) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	int *X = (int*)malloc(sizeof(int)*(unsigned int)N);
	int *Y = (int*)malloc(sizeof(int)*(unsigned int)N);

	for (int i = 0; i < N; i++) {
		cin >> X[i];
	}

	for (int i = 0; i < N; i++) {
		cin >> Y[i];
	}	

	cout << init(N,X,Y) << '\n';

	int M;
	cin >> M;

	for (int i = 0; i < M; i++) {
		int type; cin >> type;
		int pos; cin >> pos;
		int val; cin >> val;

		if (type == 1) {
			cout << updateX(pos,val) << '\n';
		} else if (type == 2) {
			cout << updateY(pos,val) << '\n';
		}
	}

	return 0;
}
