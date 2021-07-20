#include <bits/stdc++.h>

#include "grader.h"

using namespace std;

vector<int> findSequence(int N) {
    int zeroes = 0;
    for (int i = 1; i <= N; i++) {
        vector<int> tst;
        for (int j = 0; j < i; j++) tst.push_back(0);
        if (isSubsequence(tst)) zeroes++;
        else break;
    }
    vector<int> ans;
    while (zeroes) {
        int ones = 0;
        for (int i = 1; i <= N; i++) {
            vector<int> tst = ans;
            for (int j = 0; j < i; j++) tst.push_back(1);
            for (int j = 0; j < zeroes; j++) tst.push_back(0);
            if (tst.size() > N) break;
            if (isSubsequence(tst)) ones++;
            else break;
        }
        for (int i = 0; i < ones; i++) ans.push_back(1);
        ans.push_back(0);
        zeroes--;
    }
    while (ans.size() < N) ans.push_back(1);
    return ans;
}
