#include "grader.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int dp[21][1000001], indx = 1, len_at[1000001];
char char_at[1000001];

void Init() {}

void TypeLetter(char L) {
    char_at[indx] = L;
    len_at[indx] = len_at[indx - 1] + 1;

    dp[0][indx] = indx - 1;
    FOR(i, 1, 21) dp[i][indx] = dp[i - 1][dp[i - 1][indx]];

    indx++;
}

void UndoCommands(int U) {
    char_at[indx] = char_at[indx - U - 1];
    len_at[indx] = len_at[indx - U - 1];

    dp[0][indx] = dp[0][indx - U - 1];
    FOR(i, 1, 21) dp[i][indx] = dp[i - 1][dp[i - 1][indx]];

    indx++;
}

char GetLetter(int P) {
    int curr = indx - 1, x = len_at[indx - 1] - P - 1;
    for (int i = 0; x > 0; i++) {
        if (x & 1) curr = dp[i][curr];
        x >>= 1;
    }

    return char_at[curr];
}
