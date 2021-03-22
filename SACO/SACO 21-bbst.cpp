/**
 * Treap
 *
 * A balanced binary search tree that stores pairs (key, priority)
 * in a binary tree in such a way that it is a BST by key
 * and a maximum binary heap by priority.
 *
 * We assume that all keys and priorities are distinct, and we
 * generate the priorities randomly (i.e. we insert keys).
 */

#include <iostream>
#include <random>

/**
 * Generates a random integer, but better than `rand()`.
 */
long long rnd() {
    return ((rand() % (1ll << 30)) << 31) + (rand() % (1ll << 30));
}

template <class T>
struct Treap {
   private:
    struct TreapNode {
        T key;
        long long priority;
        TreapNode *l, *r;

        TreapNode(T _key)
            : key(_key), priority(rnd()), l(nullptr), r(nullptr) {}
    };

    TreapNode *_root;

    /**
     * Splits `node` into `l` and `r` so that `l` contains all elements
     * with key less than the given key, and `r` contains everything else.
     */
    void _split(TreapNode *node, T key, TreapNode *&l, TreapNode *&r) {
        if (!node)
            l = r = nullptr;
        else if (key < node->key)
            _split(node->l, key, l, node->l), r = node;
        else
            _split(node->r, key, node->r, r), l = node;
    }

    /**
     * Merges `l` and `r` into a new `TreapNode`.
     *
     * Assumes that all keys in `l` are less than all keys in `r`.
     */
    TreapNode *_merge(TreapNode *l, TreapNode *r) {
        if (!l || !r) return l ? l : r;
        if (l->priority > r->priority) {
            l->r = _merge(l->r, r);
            return l;
        }
        r->l = _merge(r->l, l);
        return r;
    }

    void _insert(TreapNode *&node, TreapNode *to_insert) {
        if (!node)
            node = to_insert;
        else if (node->priority < to_insert->priority)
            _split(node, to_insert->key, to_insert->l, to_insert->r),
                node = to_insert;
        else
            _insert(to_insert->key < node->key ? node->l : node->r, to_insert);
    }

    /**
     * Finds the value associated with a key in `node`'s subtree.
     */
    bool _find(TreapNode *node, T key) {
        if (!node) return false;
        if (node->key == key) return true;
        return _find(key < node->key ? node->l : node->r, key);
    }

    /**
     * Erases a key from `node`'s subtree.
     *
     * Assumes that the key exists in the subtree.
     */
    void _erase(TreapNode *&node, T key) {
        if (node->key == key) {
            TreapNode *tmp = node;
            node = _merge(node->l, node->r);
            delete tmp;
        } else
            _erase(key < node->key ? node->l : node->r, key);
    }

    T _min(TreapNode *node) {
        if (!node->l) return node->key;
        return _min(node->l);
    }

    T _max(TreapNode *node) {
        if (!node->r) return node->key;
        return _max(node->r);
    }

   public:
    Treap() : _root(nullptr) { srand(rnd()); }

    /**
     * Finds the value associated with a key in the treap.
     */
    bool find(T key) { return _find(_root, key); }

    /**
     * Tries to insert a key-value pair into the treap.
     */
    void insert(T key) {
        if (!find(key)) _insert(_root, new TreapNode(key));
    }

    /**
     * Tries to erase a key from the treap.
     */
    void erase(T key) {
        if (find(key)) _erase(_root, key);
    }

    /**
     * Finds the minimum key in the treap.
     */
    T min() { return _min(_root); }

    /**
     * Finds the maximum key in the treap.
     */
    T max() { return _max(_root); }
};

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    Treap<int> treap;
    char c;
    std::cin >> c;
    while (c != 'x') {
        if (c == 'i') {
            int n;
            std::cin >> n;
            while (n--) {
                int x;
                std::cin >> x;
                treap.insert(x);
            }
        } else if (c == 'r') {
            int n;
            std::cin >> n;
            while (n--) {
                int x;
                std::cin >> x;
                treap.erase(x);
            }
        } else
            std::cout << treap.min() << ' ' << treap.max() << '\n';
        std::cin >> c;
    }
}
