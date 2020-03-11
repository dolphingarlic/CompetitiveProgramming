/*
Balkan 2018 Popa
- Firstly, notice that if query(a, a, b, c), where b <= a <= c, then a is the root of the range [b, c]
- Next, notice that if we know the tree constructed from [0, i - 1], then i is either the root of that
  tree or it's some ancestor of the rightmost node (which happens to be i - 1)
- This means we can just iterate i from 0 to N - 1 and try insert i in the lowest possible position
- If we're inserting x and y is not an ancestor of x...
    - The right child of y turns into the left child of x
    - The left child of x turns into the child of y
    - We try again with the parent of y
- If y is an ancestor of x...
    - The right child of y turns into x
- If x is the root so far...
    - The left child of x turns into the previous root
    - We update the root
- Initially, this seems like it takes O(N^2) queries, but it actually only takes 2N-1 queries
- For each node we insert, we have 2 types of queries:
    - Child queries (where y is a child of x)
    - Parent queries (where y is an ancestor of x)
- Notice how there is at most 1 parent query per inserted node
- For each already-inserted node queried in a child query, there is never another query involving that node
- Therefore, there are at most 2N-1 queries
*/

#include "popa.h"

int P[1000];

int solve(int N, int* L, int* R) {
    int root = -1;
    
    for (int i = 0; i < N; i++) {
        L[i] = R[i] = P[i] = -1;
        
        int par = i - 1;
        while (par != -1 && query(i, i, par, i)) {
            R[par] = L[i];
            P[L[i]] = par;
            L[i] = par;
            int parpar = P[par];
            P[par] = i;
            par = parpar;
        }
        
        if (par == -1) {
            L[i] = root;
            if (root != -1) P[root] = i;
            root = i;
        } else {
            R[par] = i;
            P[i] = par;
        }
    }
    
    return root;
}
