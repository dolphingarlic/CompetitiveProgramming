/*
IOI 2015 Towns
- Firstly, notice that any hub must lie on the diameter of the tree
    - Additionally, there are at most 2 hubs
- Let A--B be the diameter
- Notice how any hub must also lie on the path 0--A
- To find A and B,
    - First, find the longest path from town 0 using N - 1 queries
        - The node that satisfies this is A
    - Next, find the longest path from A using N - 2 queries
        - The node that satisfies this is B
- If we have any 3 nodes, the "spanning tree" joining them has exactly
  1 node with degree == 3
    - Call that the lca[i] for towns (0, A, i)
- Since we have distances from towns 0 and A to every other town, we
  can use PIE to find the distance from A to lca[i]
- We then pick the one (or two) with smallest R and split towns into 3 categories:
    - In A's subtree if we remove the hub (int closer_to_A)
    - In 0's subtree if we remove the hub (int closer_to_0)
    - In its own subtree (vector<int> middle)
- If either closer_to_A or closer_to_0 exceed N / 2, the hub isn't balanced
- Now we simply need to check using at most 3N / 2 queries whether
  there is a majority element in middle and by how much it's the majority
- First, keep 2 lists stck and bckt, and iterate through the towns
    - If the current town and the town on top of stck are in the same
      component when the hub is removed (we can check this with 1 query),
        - Push it to bckt
    - Otherwise,
        - Push it to stck
        - If bckt.size(), push bckt.back() to stck and bckt.pop_back()
- Notice how everything in bckt is in the same component and no 2 adjacent
  elements in stck are in the same component
- Let T be stck.back()
- Next, while stck.size(),
    - If T and stck.back() are in the same component,
        - Pop the last 2 elements of stck
        - If there is only 1 element, push that element to bckt
    - Otherwise,
        - Pop the last elements of stck and bckt
        - If bckt is empty before doing this, there is no majority
- This is efficient because we only make 3N / 2 - 2 queries
- Finally, you know that there are (middle.size() + bckt.size()) / 2 of the
  majority element
- Just check if this exceeds N / 2
- Complexity: O(N^2) with at most 7N / 2 - 5 queries
*/

#include "towns.h"

#include <vector>

inline int max(int X, int Y) { return (X > Y ? X : Y); }

struct Hub {
    int dist_A, R;

    Hub(int A = 1000001, int B = 1000001) {
        dist_A = A;
        R = max(A, B);
    }
} hubs[2];

int hubDistance(int N, int sub) {
    int to_0[110], A, to_A[110], B;
    for (int i = 0, best_A = 0; i < N; i++) {
        to_0[i] = getDistance(0, i);
        if (to_0[i] > best_A) A = i, best_A = to_0[i];
    }
    for (int i = 0, best_B = 0; i < N; i++) {
        to_A[i] = getDistance(A, i);
        if (to_A[i] > best_B) B = i, best_B = to_A[i];
    }

    int hub_cnt = 0;
    for (int i = 0; i < N; i++) {
        int lca_to_A = (to_A[i] + to_A[0] - to_0[i]) / 2;
        Hub potential_hub(lca_to_A, to_A[B] - lca_to_A);

        if (!hub_cnt || potential_hub.R < hubs[0].R) {
            hub_cnt = 1;
            hubs[0] = potential_hub;
        } else if (potential_hub.R == hubs[0].R &&
                   potential_hub.dist_A != hubs[0].dist_A) {
            hub_cnt = 2;
            hubs[1] = potential_hub;
        }
    }

    int is_balanced = -1;
    for (int h = 0; h < hub_cnt; h++) {
        std::vector<int> middle, stck, bckt;
        int closer_to_A = 0, closer_to_0 = 0;
        for (int i = 0; i < N; i++) {
            int lca_to_A = (to_A[i] + to_A[0] - to_0[i]) / 2;

            if (lca_to_A == hubs[h].dist_A) middle.push_back(i);
            else if (lca_to_A < hubs[h].dist_A) closer_to_A++;
            else closer_to_0++;
        }
        if (max(closer_to_A, closer_to_0) > N / 2) continue;
        if (middle.size() <= N / 2) {
            is_balanced = 1;
            break;
        }

        for (int i : middle) {
            if (!stck.size()) {
                stck.push_back(i);
                continue;
            }
            int lca_to_A = (to_A[i] + to_A[stck.back()] - getDistance(i, stck.back())) / 2;
            if (lca_to_A == hubs[h].dist_A) {
                stck.push_back(i);
                if (bckt.size()) {
                    stck.push_back(bckt.back());
                    bckt.pop_back();
                }
            } else bckt.push_back(i);
        }

        int T = stck.back();
        while (stck.size()) {
            int lca_to_A = (to_A[T] + to_A[stck.back()] - getDistance(T, stck.back())) / 2;
            if (lca_to_A == hubs[h].dist_A) {
                stck.pop_back();
                if (bckt.size()) bckt.pop_back();
                else break;
            } else {
                stck.pop_back();
                if (stck.size()) stck.pop_back();
                else bckt.push_back(0);
            }
        }

        if (bckt.size() > N - middle.size()) continue;
        is_balanced = 1;
    }

    return hubs[0].R * is_balanced;
}
