#include "combo.h"
#include <vector>
using namespace std;

string guess_sequence(int N) {
    string S;
    vector<char> possible;

    if (press("AB")) {
        if (press("A")) {
            S = "A";
            possible = {'B', 'X', 'Y'};
        } else {
            S = "B";
            possible = {'A', 'X', 'Y'};
        }
    } else {
        if (press("X")) {
            S = "X";
            possible = {'A', 'B', 'Y'};
        } else {
            S = "Y";
            possible = {'A', 'B', 'X'};
        }
    }

    for (int i = 2; i < N; i++) {
        int k =
            press(S + possible[0] + S + possible[1] + possible[0] + S +
                  possible[1] + possible[1] + S + possible[1] + possible[2]);
        if (k == i) {
            S += possible[0];
        } else if (k == i + 1) {
            S += possible[1];
        } else {
            S += possible[2];
        }
    }

    if (N > 1) {
        if (press(S + possible[0]) == N)
            S += possible[0];
        else if (press(S + possible[1]) == N)
            S += possible[1];
        else
            S += possible[2];
    }

    return S;
}
