#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <unordered_set>
#include <vector>
using namespace std;

class Graph {
private:
	int nodeCount;
	vector<vector<int>> edges;
public:
	Graph(int n) : nodeCount(n), edges(n, vector<int>(n, -1)) {}

	void addEdge(int firstNode, int secondNode) {
		// cout << "Enter addEdge\n";
		if (firstNode >= nodeCount || secondNode >= nodeCount || firstNode < 0 || secondNode < 0) {
			throw 1;
		}
		edges.at(firstNode).at(secondNode) = 6;
		edges.at(secondNode).at(firstNode) = 6;
		// cout << "Exit addEdge\n";
	}

	vector<int> shortestPaths(int start) {
		// cout << "Begin test starting at " << start << '\n';
		vector<int> nodeDistance(nodeCount, -1);
		nodeDistance[start] = 0;

		queue<int> nodesToSearch;
		nodesToSearch.emplace(start);

		while (!nodesToSearch.empty()) {
			int current = nodesToSearch.front();
			// cout << "While, current: " << current << '\n';
			nodesToSearch.pop();

			for (int i=0; i<nodeCount; ++i) {
				if (nodeDistance[i] == -1) {
					// cout << "Currently impossible to get to " << i << '\n';
					int edgeWeight = edges.at(current).at(i);
					if (edgeWeight != -1) {
						// cout << "Edge exists between " << current << " and " << i << '\n';
						//for each node connected to current
						nodeDistance[i] = nodeDistance[current] + edgeWeight;
						// cout << "Now possible to get to " << i << " via " << nodeDistance[i] << " steps\n";
						nodesToSearch.emplace(i);
					}
				} else {
					// cout << "Already possible to get to " << i << " via " << nodeDistance[i] << " steps\n";
				}
			}
		}
		return nodeDistance;
	}
};

int main() {
	int queryCount;
	cin >> queryCount;

	for (int queryNum=0; queryNum<queryCount; queryNum++) {
		int nodeCount, edgeCount;
		cin >> nodeCount;
		// Create a graph of size nodeCount where each edge weight is 6: 
		Graph graph(nodeCount);
		cin >> edgeCount;
		// read and set edges
		for (int i=0; i<edgeCount; i++) {
			int firstNode, secondNode;
			cin >> firstNode >> secondNode;
			--firstNode;
			--secondNode;
			// add each edge to the graph
			graph.addEdge(firstNode, secondNode);
		}
		int startingNode;
		cin >> startingNode;
		startingNode--;
		// Find shortest reach from node s
		vector<int> distances = graph.shortestPaths(startingNode);

		for (size_t i=0; i<distances.size(); i++) {
			if (i != static_cast<size_t>(startingNode)) {
				cout << distances[i] << " ";
			}
		}
		cout << '\n';
	}
	return 0;
}
