/*
JOI 2020 Making Friends on Joitter is Fun!

**Time Complexity:** $\mathcal O(M \log^2 N)$.

We'll always end up with the same number of followings after a social exchange event regardless of the order in which we choose the triples $(x, y, z)$.

Consider the following graph:
- Nodes represent people on Joitter.
- There are two types of edges: red and blue.
    - Red edges are undirected and represent a mutual following
    - Blue edges are directed and represent a one-way following

The key observation is that if node $u$ can reach node $v$ using only red edges, then they will be connected with a red edge after a social exchange event. This suggests that we should use DSU to keep track of components of nodes connected by red edges.

Furthermore, if we have two separate components $A$ and $B$, four nodes $u_A, v_A \in A, u_B, v_B \in B$ (not necessarily distinct), and the blue edges $u_A \rightarrow v_B$ and $u_B \rightarrow v_A$, then each pair of nodes in $A \cup B$ will also have a red edge between them after a social exchange event. This means that we should merge $A$ and $B$ in the DSU if this ever happens.

We can use small-to-large merging to keep track of blue edges between components in $\mathcal O(M \log^2 N)$ time.

(Note that two components merging may cause other components also to merge, so also keep a queue of which components need to merge.)

Although we have a nice structure for storing and merging components, we still need to calculate the change in the answer each time two components $A$ and $B$ merge!

Let $V_i$ be the number of followings after the $i$-th merging, and let $F_S$ be the set of people outside of the component $S$ that follow someone in $S$.

1. We need to subtract the number of followings from **inside** the previously-unmerged $A$ and $B$. Since each pair of people followed each other, this number is $|A| \cdot (|A| - 1) + |B| \cdot (|B| - 1)$.
2. We need to add the number of followings from **inside** the newly-merged $A \cup B$. Since each pair of people will follow each other, this number is $|A \cup B| \cdot (|A \cup B| - 1)$.
3. We need to add the number of followings from **outside** $A \cup B$. Since people who previously followed everyone in $A$ will now also follow everyone in $B$ and vice-versa, this number is $|A| \cdot |F_B| + |B| \cdot |F_A|$.
4. We need to subtract the number of followings from people who previously already followed everyone in both $A$ and $B$ or were already in $A$ or $B$. This number is $|(A \cup F_A) \cap (B \cup F_B)| \cdot |A \cup B|$.

To make calculations a bit easier, let $C_S = S \cup F_S$.

Putting it all together, we get
$$
V_i = V_{i - 1} + |A| \cdot |C_B| + |B| \cdot |C_A| - |C_A \cap C_B| \cdot |A \cup B|
$$

We can use small-to-large merging again to keep track of each $C_S$ in $\mathcal O(M \log^2 N)$ time.
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int cmp[100001];
ll sz[100001], ans = 0;
set<int> child[100001], graph[100001], rgraph[100001];
queue<pair<int, int>> to_merge;

void insert_weak_connection(int A, int B) {
    graph[A].insert(B);
    rgraph[B].insert(A);
    // If there's A new strong connection between A's and B's components, merge them
    if (graph[B].count(A)) to_merge.push({A, B});
}

int dsu_size(int A) { return child[A].size() + graph[A].size() + rgraph[A].size(); }

int find(int A) { return (A == cmp[A] ? A : cmp[A] = find(cmp[A])); }

void onion(int A, int B) {
    if (A == B) return;
    // Merge the smaller component into the larger
    if (dsu_size(A) < dsu_size(B)) swap(A, B);

    // Add new contribution
    ans += sz[B] * child[A].size() + sz[A] * child[B].size();

    // DSU stuff
    cmp[B] = A;
    sz[A] += sz[B];

    // Merge children of B into A
    for (int i : child[B]) {
        if (child[A].count(i)) ans -= sz[A];
        else child[A].insert(i);
    }
    // Erase the connections
    graph[A].erase(B), rgraph[A].erase(B);
    graph[B].erase(A), rgraph[B].erase(A);
    // Merge the weak connections to other components
    for (int i : graph[B]) {
        rgraph[i].erase(B);
        insert_weak_connection(A, i);
    }
    for (int i : rgraph[B]) {
        graph[i].erase(B);
        insert_weak_connection(i, A);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cmp[i] = i;
        sz[i] = 1;
        child[i].insert(i);
    }
    while (m--) {
        int A, B;
        cin >> A >> B;

        B = find(B);
        // If A isn't in B's component and doesn't already follow someone in B's component...
        if (find(A) != B && !child[B].count(A)) {
            // We insert A as A follower of B and add sz[find(B)] to the answer
            child[B].insert(A);
            ans += sz[B];

            A = find(A);
            // Add connections between components
            insert_weak_connection(A, B);
            // We may have to merge multiple components for each new event
            while (to_merge.size()) {
                tie(A, B) = to_merge.front();
                to_merge.pop();
                onion(find(A), find(B));
            }
        }
        cout << ans << '\n';
    }
    return 0;
}