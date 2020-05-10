/*
COI 2014 Nizovi
- For each index i of A,
    - Find the smallest j such that A[i] < B[j] using binary search
    - Reverse [A[i], A[end]], [B[start], B[j - 1]], [A[i], B[j - 1]]
- Complexity: O(A log A) queries, O(A * A + 2 * B) cost
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int cmp(int X, int Y) {
    cout << "cmp " << X << ' ' << Y << endl;
    cin >> X;
    return X;
}

void rev(int X, int Y) {
    if (X == Y) return;
    cout << "reverse " << X << ' ' << Y << endl;
}

int main() {
    int A, B;
    cin >> A >> B;
    for (int A_ptr = 0, B_ptr = 0; A_ptr < A && B_ptr < B; A_ptr++) {
        if (cmp(A_ptr + B_ptr + 1, A + B_ptr + 1) != 1) continue;
        
        int l = A + B_ptr + 2, r = A + B + 1;
        while (l != r) {
            int mid = (l + r) / 2;
            if (cmp(A_ptr + B_ptr + 1, mid) != -1) l = mid + 1;
            else r = mid;
        }

        rev(A_ptr + B_ptr + 1, A + B_ptr);
        rev(A + B_ptr + 1, l - 1);
        rev(A_ptr + B_ptr + 1, l - 1);

        B_ptr = l - A - 1;
    }
    cout << "end" << endl;
    return 0;
}