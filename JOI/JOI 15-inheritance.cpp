#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
using namespace std;

struct Rail {
	int c, l, r, id;
};
bool operator<(Rail A, Rail B) {
	return A.c > B.c;
}

int cmp[1001][10001];
int find(int A, int K) {
	while (A != cmp[A][K]) cmp[A][K] = cmp[cmp[A][K]][K], A = cmp[A][K];
	return A;
}
void onion(int A, int B, int K) {
	cmp[find(A, K)][K] = cmp[find(B, K)][K];
}

Rail rails[300000];
int owner[300000];

int main() {
	// MST + binsearch for best child to inherit
	int n, m, k;
	cin >> n >> m >> k;
	FOR(i, 1, n + 1) FOR(j, 1, k + 1) cmp[i][j] = i;
	FOR(i, 0, m) {
		cin >> rails[i].l >> rails[i].r >> rails[i].c;
		rails[i].id = i;
	}
	sort(rails, rails + m);
	
	FOR(i, 0, m) {
		int l = 1, r = k;
		while (l != r) {
			int mid = (l + r) / 2;
			if (find(rails[i].l, mid) != find(rails[i].r, mid)) r = mid;
			else l = mid + 1;
		}
		
		if (find(rails[i].l, l) != find(rails[i].r, l)) {
			owner[rails[i].id] = l;
			onion(rails[i].l, rails[i].r, l);
		}
	}
	
	FOR(i, 0, m) {
		cout << owner[i] << '\n';
	}
	return 0;
}