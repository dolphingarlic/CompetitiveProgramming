#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool has_red[100001];
int cnt[100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    fill(cnt + 1, cnt + n + 1, 1);
    has_red[1] = true;
    while (m--) {
        int x, y;
        cin >> x >> y;
        if (has_red[x]) has_red[y] = true;
        cnt[x]--, cnt[y]++;
        if (!cnt[x]) has_red[x] = false;
    }
    cout << accumulate(has_red + 1, has_red + n + 1, 0);
    return 0;
}
