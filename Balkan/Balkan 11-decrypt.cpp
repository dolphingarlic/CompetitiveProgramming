/*
Balkan 2011 Decrypt
- Firstly, notice that R is periodic with period = 7
- We can then query random numbers until we get collisions
    - Using these collisions, we can deduce R
- After deducing R, we can easily find M
*/

#include <bits/stdc++.h>
using namespace std;

int query(int x) {
    cout << x << endl;
    int ret;
    cin >> ret;
    return ret;
}

void solution(int R[], int M[]) {
    cout << "SOLUTION" << endl;
    for (int i = 0; i < 3; i++) cout << R[i] << endl;
    for (int i = 0; i < 256; i++) cout << M[i] << endl;
}

void decrypt() {
    srand(69420);
    int R[7];
    int M[256];
    int mp[7][7] = {
        {0, 3, 6, 1, 5, 4, 2},
        {3, 1, 4, 0, 2, 6, 5},
        {6, 4, 2, 5, 1, 3, 0},
        {1, 0, 5, 3, 6, 2, 4},
        {5, 2, 1, 6, 4, 0, 3},
        {4, 6, 3, 2, 0, 5, 1},
        {2, 5, 0, 4, 3, 1, 6}
    };
    int res[7][256];
    pair<int, int> has[256];
    fill(R, R + 7, -1);
    fill(M, M + 256, -1);
    for (int i = 0; i < 7; i++) fill(res[i], res[i] + 256, -1);
    fill(has, has + 256, make_pair(-1, -1));

    int i = 0;
    for (; find(R, R + 7, -1) != R + 7; i = (i + 1) % 7) {
        int x = rand() % 256;
        while (res[i][x] != -1) x = rand() % 256;
        res[i][x] = query(x);
        if (has[res[i][x]].first != -1) {
            int idx = mp[i][has[res[i][x]].first];
            R[idx] = x ^ has[res[i][x]].second;
        }
        has[res[i][x]] = {i, x};
    }
    for (int j = 0; j < 256; j++) {
        if (has[j].first != -1) {
            M[R[has[j].first] ^ has[j].second] = j;
        }
    }
    for (int j = 0; j < 256; j++) {
        if (M[j] == -1) {
            M[j] = query(R[i] ^ j);
            i = (i + 1) % 7;
        }
    }
    solution(R, M);
}

int main() {
    decrypt();
    return 0;
}