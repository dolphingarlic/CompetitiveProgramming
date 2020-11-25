#include "wiring.h"
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

long long dp[200001], all[200001], pref_min[200001]{INF}, pref_sum[200001];
vector<pair<int, int>> clusters;

long long min_total_length(vector<int> r, vector<int> b) {
    int n = r.size() + b.size();
    
    for (int i=0, ri=0, bi=0, lc=-1, cc; i<n; ++i, lc=cc) {
        if(ri >= r.size() || bi < b.size() && b[bi] < r[ri]) {
            all[i] = b[bi++];
            cc = 0;
        } else {
            all[i] = r[ri++];
            cc = 1;
        }

        pref_sum[i + 1] = all[i] + pref_sum[i];
        if (cc != lc)
            clusters.push_back({i, i});
        else
            clusters.back().second++;
    }

    for (int i = clusters[0].first; i <= clusters[0].second; i++) dp[i + 1] = INF;
    for (int i = 0; i < clusters.size() - 1; i++) {
        for (int j = 0; j <= clusters[i].second - clusters[i].first; j++)
            pref_min[j + 1] = min(pref_min[j], min(dp[clusters[i].first + j], dp[clusters[i + 1].first]) + (clusters[i].second - clusters[i].first + 1 - j) * all[clusters[i + 1].first] + pref_sum[clusters[i].first + j]);

        long long min_2 = INF;

        for (int j = 0; j <= clusters[i + 1].second - clusters[i + 1].first; j++) {
            dp[clusters[i + 1].first + j + 1] = min_2 - (j + 1) * all[clusters[i].second];
            if (j <= clusters[i].second - clusters[i].first) {
                dp[clusters[i + 1].first + j + 1] = min(dp[clusters[i + 1].first + j + 1], pref_min[clusters[i].second - clusters[i].first + 1 - j] - (j + 1) * all[clusters[i + 1].first]);
                min_2 = min(min_2, min(dp[clusters[i].second - j], dp[clusters[i + 1].first]) + (j + 1) * all[clusters[i].second] + pref_sum[clusters[i].second - j]);
            }

            dp[clusters[i + 1].first + j + 1] += pref_sum[clusters[i + 1].first + j + 1]- 2 * pref_sum[clusters[i + 1].first];
        }
    }

    return dp[n];
}
