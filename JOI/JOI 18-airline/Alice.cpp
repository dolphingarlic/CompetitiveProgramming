/*
JOI 2018 Airline Map
- Firstly, notice that there is no limit on the number of edges
    - Since it is very difficult to extract edge data, we'd ideally want to
      send the original graph plus some extra vertices
- The main problem is identifying the node numbers
    - We can add an extra 10 "bit nodes", where bit node i and node j are
      connected only if the i-th bit of j is 1
- The next problem is identifying these "bit nodes"
    - We add another vertex connected to every node except the bit nodes
    - Also, we let the bit nodes for a chain
    - Notice that now, every node has degree at least 1
    - Add a final vertex connected to only the other special vertex
    - We can thus identify the first special vertex by the degrees of its neighbours
- Lastly, notice that the 10th bit node always has the degree less than the 1st bit node
- This approach takes 12 extra vertices
*/

#include <vector>
#include "Alicelib.h"

void Alice(int N, int M, int A[], int B[]) {
    std::vector<std::pair<int, int>> edges;
    // Original graph
    for (int i = 0; i < M; i++) edges.push_back({A[i], B[i]});
    // Bit nodes to find node numbers
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < N; j++) {
            if (j & (1 << i)) edges.push_back({N + i, j});
        }
        if (i < 9) edges.push_back({N + i, N + i + 1});
    }
    // Special vertex connected to all nodes but bit nodes
    for (int i = 0; i < N; i++) edges.push_back({N + 10, i});
    // Other vertex to identify the special vertex
    edges.push_back({N + 11, N + 10});
    // Send the graph
    InitG(N + 12, edges.size());
    for (int i = 0; i < edges.size(); i++)
        MakeG(i, edges[i].first, edges[i].second);
}
