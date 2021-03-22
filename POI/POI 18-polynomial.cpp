/*
POI 2018 Polynomial
- We use the idea behind the FFT to solve this problem
- Let dft(k, idx, W) = {W(q^ki) % M : i from 0 to N / k}
    - Our answer is dft(1, 0, W)
- If k == N, then dft(k, idx, W) = A[idx]
- Otherwise, W(x) = W_even(x^2) + x * W_odd(x^2)
- We can find ans = dft(k, idx, W) using even = dft(2k, idx, W_even) and odd = dft(2k, idx | k, W_odd)
- Case 1: i < N / 2k
    - ans[i] = W(q^ki) % M
             = (W_even(q^2ki) + q^ki * W_odd(q^2ki)) % M
             = (even[i] + q^ki * odd[i]) % M
- Case 2: i >= N / 2k
    - Write i as N / 2k + j
        - Note that j = i % (N / 2k)
    - ans[i] = W(q^(N / 2 + kj)) % M
             = (W_even(q^N * q^2kj) + q^ki * W_odd(q^N * q^2kj)) % M
             = (W_even(q^2kj) + q^ki * W_odd(q^2kj)) % M  (since q^N % N = 1)
             = (even[j] + q^ki * odd[j]) % M
- Putting the two cases together, we get
    ans[i] = (even[i % (N / 2k)] + q^ki * odd[i % (N / 2k)]) % M
- Each layer of recursion takes O(N) time to compute and there are O(log N) layers,
  so the time complexity is O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
ll m, q, a[1 << 20], q_pow[1 << 20];

vector<ll> dft(int k = 1, int idx = 0) {
    if (k == n) return {a[idx]};
    else {
        vector<ll> even = dft(k * 2, idx);
        vector<ll> odd = dft(k * 2, idx | k);

        int split = n / k / 2;
        vector<ll> ans;
        for (int i = 0; i < 2 * split; i++)
            ans.push_back((even[i % split] + q_pow[k * i] * odd[i % split] % m) % m);
        return ans;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> a[i];

    q_pow[0] = 1;
    for (int i = 1; i < n; i++) q_pow[i] = q * q_pow[i - 1] % m;

    vector<ll> ans = dft();
    ll tot = 0;
    for (ll i : ans) tot = (tot + i) % m;
    cout << tot << '\n';
    for (int i = 1; i < n; i++) cout << ans[i] << ' ';
    cout << ans[0];
    return 0;
}
