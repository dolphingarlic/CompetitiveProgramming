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
#include "Boblib.h"

std::vector<int> graph[1012];
bool adj[1012][1012], is_bit[1012], visited[1012];
int actual[1012];

void Bob(int V, int U, int C[], int D[]) {
	for (int i = 0; i < U; i++) {
		graph[C[i]].push_back(D[i]);
		graph[D[i]].push_back(C[i]);
		adj[C[i]][D[i]] = adj[D[i]][C[i]] = true;
	}
	// Find the 2 special vertices
	int special;
	for (int i = 0; i < V; i++) {
		if (graph[i].size() == 1 && graph[graph[i][0]].size() == V - 11) {
			special = graph[i][0];
			break;
		}
	}
	is_bit[special] = true;
	// Identify the bit vertices
	int last_bit = special;
	for (int i = 0; i < V; i++) {
		if (i != special && !adj[i][special]) {
			is_bit[i] = true;
			if (graph[i].size() <= graph[last_bit].size()) last_bit = i;
		}
	}
	for (int i = 9; ~i; i--) {
		visited[last_bit] = true;
		for (int j : graph[last_bit]) actual[j] += 1 << i;
		for (int j : graph[last_bit]) if (is_bit[j] && !visited[j]) {
			last_bit = j;
			break;
		}
	}
	// Construct the graph again
	std::vector<std::pair<int, int>> edges;
	for (int i = 0; i < V; i++) for (int j = i + 1; j < V; j++) {
		if (adj[i][j] && !is_bit[i] && !is_bit[j]) edges.push_back({actual[i], actual[j]});
	}
	InitMap(V - 12, edges.size());
	for (std::pair<int, int> i : edges) MakeMap(i.first, i.second);
}
