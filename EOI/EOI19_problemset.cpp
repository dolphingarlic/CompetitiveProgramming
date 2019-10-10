#include <bits/stdc++.h>

using namespace std;

vector<int> Encode(vector<int> a, int st) {
    map<int, int> s;
    for (int i : a) s[i]++;

    vector<int> ret = {0};
    for (auto& i : s) for (int j = 0; j <= i.second; j++) ret.push_back(i.first);
    return ret;
}

vector<int> Decode(int n, vector<int> em, int st) {
    map<int, int> s;
    for (int i : em) s[i]++;
    
    for (auto& i : s) {
        if (i.second == 1) {
            vector<int> ret;
            for (auto& j : s) {
                if (j == i) continue;
                for (int k = 1; k < j.second; k++) ret.push_back(j.first ^ i.first);
            }
            sort(ret.begin(), ret.end());
            return ret;
        }
    }
}

void WA(const char *msg) {
    printf("WA: %s\n", msg);
    exit(0);
}

double score[7] = {0, 5, 8, 18, 9, 50, 10};
const int Aenc[5] = {43223232, 24421132, 13423222, 34252334, 231234332};
const int Xenc[5] = {99123232, 12132229, 22132193, 92132293, 321122923};
int MAXA = (1 << 12) - 1, MINA = 0;

int main() {
    int t, st;
    scanf("%d %d", &t, &st);
    if (st == 6) MAXA = (1 << 20) - 1;
    for (int tt = 0; tt < t; tt++) {
        srand(1234);
        int n, x;
        scanf("%d %d", &n, &x);
        if (t > 10) x ^= Xenc[tt % 5];
        vector<int> a;
        for (int i = 0; i < n; i++) {
            int val;
            scanf("%d", &val);
            if (t > 10) val ^= Aenc[(i + tt) % 5];
            a.push_back(val);
        }
        vector<int> v = Encode(a, st);
        if (v.size() > 3 * n) WA("The length of the array can\'t exceed 3*n");
        for (int i = 0; i < v.size(); i++) {
            if (v[i] > MAXA || v[i] < MINA) WA("Invalid array values");
            v[i] ^= x;
        }
        if (st != 2) {
            for (int i = 1; i < v.size(); i++) swap(v[i], v[rand() % i]);
        }
        vector<int> ans = Decode(n, v, st);
        if (ans != a) {
            WA("guessed A incorrectly");
        }
        double curscore = score[st];
        if (st == 5) {
            if (v.size() > 4100 && v.size() <= 4300)
                curscore = 50 - 20 * (v.size() - 4100) / 200.0;
            else if (v.size() > 4300)
                curscore = 30 - 8 * log2((v.size() - 3300) / 1000.0);
        }
        if (st == 6) {
            if (v.size() > 4300) curscore = 0;
        }
        printf("AlfAlfMabrouk: %.6lf\n", curscore);
    }
    printf("828d299f29a9b1e\n");
}