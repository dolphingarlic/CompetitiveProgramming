#include <cassert>
#include <cstdio>
#include <map>

int N;
int ft[200005];

void update(int i, int v) {
    for (; i <= N * 2; i += (i & -i)) {
        ft[i] += v;
    }
}

int query(int i) {
    int ac = 0;
    for (; i > 0; i -= (i & -i)) {
        ac += ft[i];
    }
    return ac;
}

int uf[100005];

int find(int a) { return (a == uf[a]) ? a : (uf[a] = find(uf[a])); }

void merge(int a, int b) { uf[find(a)] = find(b); }

int st_lazy[800005];  // lazy merge with range, only nonzero if st_cnt is
                      // nonzero
int st_cnt[800005];

int who[200005];  // who[l]=who[r]=id

void apply(int w, int v) {
    if (!st_cnt[w]) return;
    if (st_lazy[w]) {
        merge(v, st_lazy[w]);
    } else {
        st_lazy[w] = v;
    }
}

void push(int w, int L, int R) {
    if (st_lazy[w]) {
        if (R - L > 1) {
            apply(w * 2 + 1, st_lazy[w]);
            apply(w * 2 + 2, st_lazy[w]);
        } else {
            merge(st_lazy[w], who[R]);
        }
        st_lazy[w] = 0;
    }
}

void pull(int w, int L, int R) {
    assert(R - L > 1);
    st_cnt[w] = st_cnt[w * 2 + 1] + st_cnt[w * 2 + 2];
}

void update_range_merge(int w, int L, int R, int a, int b, int v) {
    push(w, L, R);
    if (a >= R || b <= L) return;
    if (a <= L && b >= R) {
        apply(w, v);
        push(w, L, R);
    } else {
        int M = (L + R) / 2;
        update_range_merge(w * 2 + 1, L, M, a, b, v);
        update_range_merge(w * 2 + 2, M, R, a, b, v);
        pull(w, L, R);
    }
}

void update_inc(int w, int L, int R, int i, int v) {
    push(w, L, R);
    if (i <= L || i > R) return;
    if (R - L == 1) {
        st_cnt[w] += v;
    } else {
        int M = (L + R) / 2;
        update_inc(w * 2 + 1, L, M, i, v);
        update_inc(w * 2 + 2, M, R, i, v);
        pull(w, L, R);
    }
}

void force_lazy(int w, int L, int R) {
    push(w, L, R);
    if (R - L > 1) {
        int M = (L + R) / 2;
        force_lazy(w * 2 + 1, L, M);
        force_lazy(w * 2 + 2, M, R);
    }
}

struct Event {
    int l, r;
    bool start;
    int id;
} events[200005];

int exterior[100005];

bool vis[100005];

int main() {
    int T;
    scanf("%d %d", &N, &T);
    for (int i = 1; i <= N; i++) {
        int X1, Y1, X2, Y2;
        scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
        events[X1] = Event{Y1, Y2, true, i};
        events[X2] = Event{Y1, Y2, false, i};
        who[Y1] = i;
        who[Y2] = i;
    }
    for (int i = 1; i <= N; i++) {
        uf[i] = i;
    }
    int corners[2] = {0, 0};  // 0:exterior white, 1:exterior black
    long long intersections = 0;
    std::map<int, int> active;
    for (int x = 1; x <= N * 2; x++) {
        int l = events[x].l, r = events[x].r, id = events[x].id;
        if (events[x].start) {
            exterior[id] = query(l) % 2;
            corners[query(l) % 2]++;
            corners[query(r) % 2]++;
            intersections += query(r) - query(l);
            update_range_merge(0, 0, N * 2, l, r, id);
            update(l, 1);
            update(r, 1);
            update_inc(0, 0, N * 2, l, 1);
            update_inc(0, 0, N * 2, r, 1);
        } else {
            update(l, -1);
            update(r, -1);
            update_inc(0, 0, N * 2, l, -1);
            update_inc(0, 0, N * 2, r, -1);
            intersections += query(r) - query(l);
            update_range_merge(0, 0, N * 2, l, r, id);
            corners[query(l) % 2]++;
            corners[query(r) % 2]++;
        }
    }
    force_lazy(0, 0, N * 2);
    int black_immersed = 0, white_immersed = 0;  // cc surrounded by black/white
    for (int x = 1; x <= N * 2; x++) {
        int id = events[x].id;
        if (events[x].start) {
            if (!vis[find(id)]) {
                if (exterior[id]) {
                    black_immersed++;
                } else {
                    white_immersed++;
                }
                vis[find(id)] = true;
            }
        }
    }
    long long black_corners = corners[0] - corners[1] + intersections * 2;
    long long white_corners = corners[1] - corners[0] + intersections * 2;
    assert(black_corners % 4 == 0);
    assert(white_corners % 4 == 0);
    long long black_regions = black_corners / 4 + black_immersed;
    long long white_regions = white_corners / 4 + white_immersed + 1;
    if (T == 1) {
        printf("%lld\n", white_regions + black_regions);
    } else {
        printf("%lld %lld\n", white_regions, black_regions);
    }
}
