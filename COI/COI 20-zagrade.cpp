#include <bits/stdc++.h>
using namespace std;

bool guess(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    bool res;
    cin >> res;
    return res;
}

char ans[100001];

int main() {
    int n, q, rem;
    cin >> n >> q;
    rem = n / 2;
    stack<int> stck;
    for (int i = 1; i <= n; i++) {
        if (!stck.size()) stck.push(i);
        else if (guess(stck.top(), i)) {
            ans[stck.top()] = '(';
            ans[i] = ')';
            stck.pop();
            rem--;
        } else stck.push(i);
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        if (ans[i] == '(' || ans[i] == ')') cout << ans[i];
        else if (rem) {
            cout << ')';
            rem--;
        } else cout << '(';
    }
    cout << endl;
    return 0;
}