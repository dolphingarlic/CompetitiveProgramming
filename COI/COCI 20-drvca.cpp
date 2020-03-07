#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

multiset<int> msa, msb, msc;
vector<int> a, b;

void finish() {
    cout << a.size() << '\n';
    for (int i : a) cout << i << ' ';
    cout << '\n' << b.size() << '\n';
    for (int i : b) cout << i << ' ';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        msa.insert(x);
        msb.insert(x);
        msc.insert(x);
    }

    // Case 1: first and second elements in a line
    a.push_back(*msa.begin());
    msa.erase(msa.begin());
    a.push_back(*msa.begin());
    msa.erase(msa.begin());
    while (msa.find(2 * a[a.size() - 1] - a[a.size() - 2]) != msa.end()) {
        msa.erase(msa.find(2 * a[a.size() - 1] - a[a.size() - 2]));
        a.push_back(2 * a[a.size() - 1] - a[a.size() - 2]);
    }
    for (int i : msa) b.push_back(i);
    bool possible = true;
    FOR(i, 1, b.size()) if (b[i] - b[i - 1] != b[1] - b[0]) {
        possible = false;
        break;
    }
    if (possible && b.size()) {
        finish();
        return 0;
    }

    // Case 2: first and second elements in separate lines
    a.clear();
    b.clear();
    a.push_back(*msb.begin());
    msb.erase(msb.begin());
    b.push_back(*msb.begin());
    msb.erase(msb.begin());
    if (n > 2) {
        a.push_back(*msb.begin());
        msb.erase(msb.begin());
    }
    while (msb.find(2 * a[a.size() - 1] - a[a.size() - 2]) != msb.end()) {
        msb.erase(msb.find(2 * a[a.size() - 1] - a[a.size() - 2]));
        a.push_back(2 * a[a.size() - 1] - a[a.size() - 2]);
    }
    for (int i : msb) b.push_back(i);
    possible = true;
    FOR(i, 1, b.size()) if (b[i] - b[i - 1] != b[1] - b[0]) {
        possible = false;
        break;
    }
    if (possible) {
        finish();
        return 0;
    }

    a.clear();
    b.clear();
    a.push_back(*msc.begin());
    msc.erase(msc.begin());
    b.push_back(*msc.begin());
    msc.erase(msc.begin());
    if (n > 2) {
        b.push_back(*msc.begin());
        msc.erase(msc.begin());
    }
    while (msc.find(2 * b[b.size() - 1] - b[b.size() - 2]) != msc.end()) {
        msc.erase(msc.find(2 * b[b.size() - 1] - b[b.size() - 2]));
        b.push_back(2 * b[b.size() - 1] - b[b.size() - 2]);
    }
    for (int i : msc) a.push_back(i);
    possible = true;
    FOR(i, 1, a.size()) if (a[i] - a[i - 1] != a[1] - a[0]) {
        possible = false;
        break;
    }
    if (possible) {
        finish();
        return 0;
    }

    cout << -1;
    return 0;
}