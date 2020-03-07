#include <bits/stdc++.h>
using namespace std;

int n, k, a;
int st, dr;
vector<int> pr;
bool gg[10000002];

void ciur() {
    for (int i = 2; i <= 10000000; ++i)
        if (!gg[i]) {
            for (int j = i; j <= 10000000; j += i) gg[j] = 1;
            pr.push_back(i);
        }
}

int simulate(int start) {
    for (int i = 0; i < k; i++) {
        int p = pr[i];
        if (start == 0)
            start = p % n;
        else {
            start = (start - (p / n) % (n - 1) + n - 2) % (n - 1);
            if (start >= p % n) start++;
        }
    }
    return start;
}
int simulateback(int start) {
    for (int i = k - 1; i >= 0; --i) {
        int p = pr[i];
        if (start == p % n)
            start = 0;
        else {
            if (start > p % n) --start;
            start = (start + (p / n) % (n - 1)) % (n - 1);
            ++start;
        }
    }
    return start;
}

int main() {
    cin >> n >> k >> a;
    ciur();
    a = simulate(a - 1);
    cout << simulateback((a + 1) % n) + 1 << ' '
         << simulateback((a - 1 + n) % n) + 1 << '\n';
    return 0;
}