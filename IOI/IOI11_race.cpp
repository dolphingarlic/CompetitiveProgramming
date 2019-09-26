#include <bits/stdc++.h>
//#include "race.h"
 
using namespace std;
 
const int N = 2e5 + 7;
const int inf = 1e9;
const int K = 1e6 + 7;
const int T = 1e8;
 
int n, k;
vector <int> adj[N], len[N], adj_c[N], rv;
int sz[N];
 
bool used[N];
 
int find_cnt(int u, int p = -1){
	sz[u] = 1;
 
	for(int to: adj[u]){
		if(p == to || used[to]){
			continue;
		}
 
		sz[u] += find_cnt(to, u);
	}
 
	return sz[u];
}
 
int find_centroid(int u, int cnt, int p = -1){
	for(int to: adj[u]){
		if(to == p || used[to]){
			continue;
		}
 
		if(sz[to] > (cnt / 2)){
			return find_centroid(to, cnt, u);
		}
	}
 
	return u;
}	
 
int root;
 
void decompose(int u, int p = -1){
	int cnt = find_cnt(u);
	int cen = find_centroid(u, cnt);
 
	//cout << p << " -> " << cen << endl;
 
	if(p != -1){
		adj_c[p].push_back(cen);
	}
	else{
		root = cen;
	}
 
	used[cen] = true;
	for(int to: adj[cen]){
		if(!used[to]){
			decompose(to, cen);
		}
	}
	used[cen] = false;
}
 
int arr[K];
vector<pair<int, int> > vec;
 
int ans = inf;
 
void solve_k(int u, int pr, int sum, int d){
	if(sum > k || used[u]){
		return;
	}
 
	vec.push_back({sum, d});
	if(arr[k - sum] != inf){
		ans = min(ans, d + arr[k - sum]);
	}
 
	for(int i = 0; i < adj[u].size(); i++){
		int to = adj[u][i];
		int l = len[u][i];
 
		if(used[to] || to == pr){
			continue;
		}
 
		solve_k(to, u, sum + l, d + 1);
	}
}
 
int sum_vec = 0;
 
clock_t t;
 
inline float time_passed(){
	return (float)(clock() - t) / (float)CLOCKS_PER_SEC;
}
 
void solve(int u){
	used[u] = true;
	for(int to: adj_c[u]){
		solve(to);
	}
	rv.clear();
 
	/*if(time_passed() > (float)2.7){
		return;
	}*/
	
	for(int i = 0; i < adj[u].size(); i++){
		vec.clear();
		solve_k(adj[u][i], u, len[u][i], 1);
 
		sum_vec += vec.size();
 
		for(pair<int, int> p: vec){
			if(arr[p.first] == inf){
				rv.push_back(p.first);
			}
			arr[p.first] = min(arr[p.first], p.second);
		}
	}
 
	for(int i: rv){
		arr[i] = inf;
	}
	
	used[u] = false;
}
 
 
 
int best_path(int _n, int _k, int _h[][2], int _l[]){
 	t = clock();
 
	n = _n;
	k = _k;
 
	for(int i = 0; i < n - 1; i++){
		adj[_h[i][0]].push_back(_h[i][1]);
		adj[_h[i][1]].push_back(_h[i][0]);
 
		len[_h[i][0]].push_back(_l[i]);
		len[_h[i][1]].push_back(_l[i]);
	}
 
	decompose(0);
 
	for(int i = 1; i < K; i++){
		arr[i] = inf;
	}
 
	solve(root);
 
	/*if(sum_vec > T){
		return -21;
	}*/
 
	if(ans == inf){
		return -1;
	}
 
	return ans;
}