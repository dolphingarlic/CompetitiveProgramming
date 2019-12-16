#include "game.h"
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll gcd(ll x, ll y) { return !y ? x : gcd(y, x % y); }
int rnd() { return ((rand() % (1 << 15)) << 16) + (rand() % (1 << 15)); }

struct TreapNode {
    TreapNode *l, *r;
    int pos, key, mn, mx;
    ll val, g;
    
    TreapNode(int position, ll value) {
        l = r = nullptr;
        mn = mx = pos = position;
        key = rnd();
        val = g = value;
    }

    void update() {
        g = val;
        if (l) g = gcd(g, l->g);
        if (r) g = gcd(g, r->g);
        mn = (l ? l->mn : pos);
        mx = (r ? r->mx : pos);
    }
};

struct Treap {
    TreapNode *root;

    Treap() {
        root = nullptr;
        srand(rnd());
    }

    void split(TreapNode *t, int pos, TreapNode *&l, TreapNode *&r) {
        if (t == nullptr) {
            l = r = nullptr;
            return;
        }
        if (t->pos < pos) {
            split(t->r, pos, l, r);
            t->r = l;
            l = t;
        } else {
            split(t->l, pos, l, r);
            t->l = r;
            r = t;
        }
        t->update();
    }

    TreapNode* merge(TreapNode *l, TreapNode *r) {
        if (!l || !r) return l ? l : r;
        if (l->key < r->key) {
            l->r = merge(l->r, r);
            l->update();
            return l;
        } else {
            r->l = merge(l, r->l);
            r->update();
            return r;
        }
    }

    bool find(int pos) {
        TreapNode *t = root;
        while (t) {
            if (t->pos == pos) return true;
            if (t->pos > pos) t = t->l;
            else t = t->r;
        }
        return false;
    }

    void update(TreapNode *t, int pos, ll val) {
        if (t->pos == pos) {
            t->val = val;
            t->update();
            return;
        }
        if (t->pos > pos) update(t->l, pos, val);
        else update(t->r, pos, val);
        t->update();
    }

    void insert(int pos, ll val) {
        if (find(pos)) update(root, pos, val);
        else {
            TreapNode *l, *r;
            split(root, pos, l, r);
            root = merge(merge(l, new TreapNode(pos, val)), r);
        }
    }

    ll query(TreapNode *t, int st, int en) {
        if (t->mx < st || en < t->mn) return 0;
        if (st <= t->mn && t->mx <= en) return t->g;
        
        ll ans = (st <= t->pos && t->pos <= en ? t->val : 0);
        if (t->l) ans = gcd(ans, query(t->l, st, en));
        if (t->r) ans = gcd(ans, query(t->r, st, en));
        return ans;
    }
    ll query(int st, int en) {
        if (!root) return 0;
        return query(root, st, en);
    }
};

struct Segtree {
    Segtree *l, *r;
    Treap treap;
    int lo, hi;

    Segtree() { l = r = nullptr; }
    Segtree(int st, int en) {
        l = r = nullptr;
        lo = st, hi = en;
    }

    void new_left() {
        if (!l) l = new Segtree(lo, (lo + hi) / 2);
    }
    void new_right() {
        if (!r) r = new Segtree((lo + hi) / 2 + 1, hi);
    }
    void fix(int pos) {
        ll val = 0;
        if (l) val = gcd(val, l->treap.query(pos, pos));
        if (r) val = gcd(val, r->treap.query(pos, pos));
        treap.insert(pos, val);
    }

    void update(int x, int y, ll val) {
        if (hi < x || x < lo) return;
        if (lo == hi) {
            treap.insert(y, val);
            return;
        }

        if (x <= (lo + hi) / 2) {
            new_left();
            l->update(x, y, val);
        } else {
            new_right();
            r->update(x, y, val);
        }
        fix(y);
    }

    ll query(int t, int b, int st, int en) {
        if (hi < t || b < lo) return 0;
        if (t <= lo && hi <= b) return treap.query(st, en);

        ll ans = 0;
        if (l) ans = gcd(ans, l->query(t, b, st, en));
        if (r) ans = gcd(ans, r->query(t, b, st, en));
        return ans;
    }
};

Segtree segtree;

void init(int R, int C) {
    srand(12341234);
    segtree = Segtree(0, R - 1);
}

void update(int P, int Q, ll K) { segtree.update(P, Q, K); }

ll calculate(int P, int Q, int U, int V) {
    return segtree.query(P, U, Q, V);
}
