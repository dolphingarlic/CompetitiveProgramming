#include "rail.h"
#include <bits/stdc++.h>
using namespace std;

int A = 0, B, C, D;
int from_A[5001], from_B[5001], visited[1000001];

bool left_cmp(int X, int Y) { return from_B[X] < from_B[Y]; }
bool right_cmp(int X, int Y) { return from_A[X] < from_A[Y]; }

void findLocation(int N, int first, int location[], int stype[]) {
    location[A] = first;
    visited[location[A]] = stype[A] = 1;

    int min_from_A = INT_MAX;
    for (int i = 1; i < N; i++) {
        from_A[i] = getDistance(A, i);
        if (from_A[i] < min_from_A) {
            min_from_A = from_A[i];
            B = i;
        }
    }

    location[B] = first + from_A[B];
    visited[location[B]] = stype[B] = 2;

    vector<int> left, right;

    for (int i = 1; i < N; i++) {
        if (i == B) continue;
        from_B[i] = getDistance(B, i);
        if (from_B[i] < from_A[B] && i != 2222) {
            location[i] = location[B] - from_B[i];
            visited[location[i]] = stype[i] = 1;
        } else if (from_A[B] + from_B[i] == from_A[i]) left.push_back(i);
        else right.push_back(i);
    }

    sort(left.begin(), left.end(), left_cmp);
    sort(right.begin(), right.end(), right_cmp);

    C = A;
    for (int i : left) {
        int from_C = getDistance(C, i);
        int z = from_B[i] - from_C - from_B[C];

        if (visited[location[C] - z / 2] == 1) {
            location[i] = location[C] + from_C;
            stype[i] = 2;
        } else {
            location[i] = location[B] - from_B[i];
            stype[i] = 1;
            C = i;
        }

        visited[location[i]] = stype[i];
    }

    D = B;
    for (int i : right) {
        int from_D = getDistance(D, i);
        int z = from_A[i] - from_D - from_A[D];

        if (visited[location[D] + z / 2] == 2) {
            location[i] = location[D] - from_D;
            stype[i] = 1;
        } else {
            location[i] = location[A] + from_A[i];
            stype[i] = 2;
            D = i;
        }

        visited[location[i]] = stype[i];
    }

    // for (int i = 0; i < N; i++) cout << stype[i] << ' ' << location[i] << '\n';
}
