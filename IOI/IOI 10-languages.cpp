/*
IOI 2010 Languages
- Sentences of the same language tend to have similar words and letters
- This means the combinations of letters are similar
    - More specifically, single letters, bigrams, trigrams, and four-grams
- If we count the frequency of the n-grams from previous queries, we can
  somewhat accurately match the language by assigning weights to each n
- The code below has a 92.6% accuracy, which gets us 101 points
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;

#include "grader.h"

const int SZ = 100, LANGS = 56, MOD = 539653;

ll si[SZ], bi[SZ], tr[SZ], qu[SZ];
double cnt[LANGS];
int freq[LANGS][MOD];

inline double hyperb(int x) { return x / (x + 1.1); }

void excerpt(int *E) {
    FOR(i, 0, SZ - 3) {
        si[i] = E[i];
        bi[i] = ((si[i] << 16) + E[i + 1]) % MOD;
        tr[i] = ((bi[i] << 16) + E[i + 2]) % MOD;
        qu[i] = ((tr[i] << 16) + E[i + 3]) % MOD;
    }

    int best = 0;
    double best_sim = 0;
    FOR(i, 0, LANGS) {
        double sim = 0;
        FOR(j, 0, SZ - 3) {
            sim += hyperb(freq[i][qu[j]]) * 138;
            sim += hyperb(freq[i][tr[j]]) * 60;
            sim += hyperb(freq[i][bi[j]]) * 97;
            sim += hyperb(freq[i][si[j]]) * 1;
        }
        sim /= log(cnt[i] + 2);

        if (sim > best_sim) best = i, best_sim = sim;
    }

    int ans = language(best);
    cnt[ans]++;
    FOR(i, 0, SZ - 3) {
        freq[ans][qu[i]]++;
        freq[ans][tr[i]]++;
        freq[ans][bi[i]]++;
        freq[ans][si[i]]++;
    }
}