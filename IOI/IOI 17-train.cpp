#include "train.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
 
vector<int> graph[5000];
bool arezou[5000], charging[5000], inactive[5000];
bool in_f_a[5000], in_f_b[5000];
int f_a, f_b, deg_in[5000];
 
vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
    int n = a.size(), m = u.size();
    // Reverse edges
    FOR(i, 0, m) graph[v[i]].push_back(u[i]);
    FOR(i, 0, n) arezou[i] = a[i], charging[i] = r[i];
 
    vector<int> stations(n);
    FOR(i, 0, n) stations[i] = i;
    
    vector<int> res(n, 0);
    while (true) {
        for (int i : stations) {
            in_f_a[i] = in_f_b[i] = false;
            deg_in[i] = 0;
        }
        f_a = f_b = 0;
 
        FOR(i, 0, m) if (!inactive[u[i]] && !inactive[v[i]]) deg_in[u[i]]++;
 
        queue<int> q;
 
        for (int i : stations) if (charging[i]) {
            in_f_a[i] = true;
            f_a++;
            q.push(i);
        }
        while (q.size()) {
            int curr = q.front();
            q.pop();
            for (int i : graph[curr]) {
                deg_in[i]--;
                if (!in_f_a[i] && !inactive[i] && (arezou[i] || !deg_in[i])) {
                    q.push(i);
                    in_f_a[i] = true;
                    f_a++;
                }
            }
        }
        if (f_a == stations.size()) {
            for (int i : stations) res[i] = true;
            break;
        }
 
        for (int i : stations) deg_in[i] = 0;
        FOR(i, 0, m) if (!inactive[u[i]] && !inactive[v[i]]) deg_in[u[i]]++;
 
        for (int i : stations) if (!in_f_a[i]) {
            in_f_b[i] = true;
            f_b++;
            q.push(i);
        }
        while (q.size()) {
            int curr = q.front();
            q.pop();
            for (int i : graph[curr]) {
                deg_in[i]--;
                if (!in_f_b[i] && !inactive[i] && (!arezou[i] || !deg_in[i])) {
                    q.push(i);
                    in_f_b[i] = true;
                    f_b++;
                }
            }
        }
        if (f_b == stations.size()) break;
 
        vector<int> new_stations;
        for (int i : stations) {
            if (!in_f_b[i]) new_stations.push_back(i);
            else inactive[i] = true;
        }
        stations = new_stations;
    }
 
    return res;
}
