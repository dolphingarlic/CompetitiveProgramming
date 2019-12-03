#include <cstdio>
#include <vector>
#include "library.h"
using namespace std;

vector<int> known;

int getNext(int s, vector<int> &pnext) {
    vector<int> pnlist;
    int N = pnext.size();
    for (int i = 0; i < N; ++i) {
        if (pnext[i] == 1) pnlist.push_back(i);
    }
    if (pnlist.size() == 1) return pnlist[0];
    vector<int> pnfirst(N), pnsec(N);
    for (int i = 0; i < pnlist.size(); ++i) {
        if (i < pnlist.size() / 2)
            pnfirst[pnlist[i]] = 1;
        else
            pnsec[pnlist[i]] = 1;
    }
    int withoutStart = Query(pnfirst);
    pnfirst[s] = 1;
    if (withoutStart != Query(pnfirst)) {
        return getNext(s, pnsec);
    } else {
        pnfirst[s] = 0;
        return getNext(s, pnfirst);
    }
}

void Solve(int N) {
    if (N == 1) {
        Answer({1});
        return;
    }
    int start = -1;
    vector<int> toQuery(N, 1);
    for (int i = 0; i < N; ++i) {
        toQuery[i] = 0;
        if (Query(toQuery) == 1) {
            start = i;
            break;
        }
        toQuery[i] = 1;
    }
    vector<int> ans{start};
    for (int i = 1; i < N; ++i) {
        vector<int> probableNext(N, 1);
        for (int x : ans) probableNext[x] = 0;
        ans.push_back(getNext(ans.back(), probableNext));
    }
    vector<int> retVal;
    for (int x : ans) retVal.push_back(x + 1);
    Answer(retVal);
}