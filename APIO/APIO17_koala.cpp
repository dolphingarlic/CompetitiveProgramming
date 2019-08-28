#include "koala.h"
#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int B[100], R[100];

/*
HELPER FUNCTIONS
*/

bool compare(int a, int b, int N, int W) {
    fill(B, B + N, 0);
    B[a] = B[b] = W;
    playRound(B, R);
    return (R[b] > W);
}
vector<int> mergesort(vector<int> v, int N, int W) {
    if (v.size() == 1) return v;
 
    vector<int> a, b;
    a.insert(a.begin(), v.begin(), v.begin() + (v.size() + 1) / 2);
    b.insert(b.begin(), v.begin() + (v.size() + 1) / 2, v.end());
    a = mergesort(a, N, W), b = mergesort(b, N, W);
 
    vector<int> sorted;
    int aptr = 0, bptr = 0;
    while (aptr < a.size() && bptr < b.size()) {
        if (compare(a[aptr], b[bptr], N, W)) sorted.push_back(a[aptr++]);
        else sorted.push_back(b[bptr++]);
    }
    sorted.insert(sorted.end(), a.begin() + aptr, a.end());
    sorted.insert(sorted.end(), b.begin() + bptr, b.end());
 
    return sorted;
}

/*
BEGIN ACTUAL FUNCTIONS
*/

// Assign a single stone to the first cup
// If Koala picks that cup, it is not the smallest and some other cup has 0
// Otherwise, cup 0 is the smallest cup
// Uses 1 turn
int minValue(int N, int W) {
    fill(B, B + N, 0);
    fill(R, R + N, 0);
    B[0] = 1;
    playRound(B, R);
    if (R[0] < 2) return 0;
    else FOR(i, 1, N) if (!R[i]) return i;
    return -1;
}

// Binary search for the max value
// Uses like 4 turns
int maxValue(int N, int W) {
    vector<int> v;
    FOR(i, 0, N) v.push_back(i);
    while (v.size() != 1) {
        int k = W / v.size();
        fill(B, B + N, 0);
        for (int i : v) B[i] = k;
        playRound(B, R);
        v.clear();
        FOR(i, 0, N)
        if (R[i] > k) v.push_back(i);
    }
    return v[0];
}

// Assign positions 0 and 1 x stones until Koala treats them differently
// Binary search for x:
// If both 0 and 1 get > x stones, increase x
// If both 0 and 1 get < x stones, decrease x
// Notice how x <= 9 because sum(9..17) > 100
// Uses like 3 turns
int greaterValue(int N, int W) {
    int l = 1, r = 9;
    while (l != r) {
        int mid = (l + r) / 2;
        B[0] = B[1] = mid;
        playRound(B, R);

        if (R[0] > mid && R[1] > mid) l = mid + 1;
        else if (R[0] <= mid && R[1] <= mid) r = mid - 1;
        else return (R[0] < R[1]);
    }
    B[0] = B[1] = l;
    playRound(B, R);
    return (R[0] < R[1]);
}

// Subtask 4:
// Assign indices i and j 100 stones each to check whether P[i] > P[j]
// Use merge sort to get O(Nlog(N)) <= 700 turns
// Subtask 5:
// TODO
void allValues(int N, int W, int *P) {
    if (W == 2 * N) {
        vector<int> v;
        FOR(i, 0, N)
        v.push_back(i);
        vector<int> sorted = mergesort(v, N, W / 2);
        FOR(i, 0, N)
        P[sorted[i]] = i + 1;
    } else {
        // TODO: Implement Subtask 5 solution here.
        // You may leave this block unmodified if you are not attempting this
        // subtask.
    }
}