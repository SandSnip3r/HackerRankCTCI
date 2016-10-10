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
		edges.at(firstNode).at(secondNode) = 6;
	}

	vector<int> shortestPaths(int start) {
		map<int,int> nodeDistance;
		for (int i=0; i<nodeCount; ++i) {
			nodeDistance.emplace(i, -1);
		}
		nodeDistance[start] = 0;

		queue<int> nodesToSearch;
		nodesToSearch.emplace(start);

		while (!nodesToSearch.empty()) {
			int current = nodesToSearch.front();
			nodesToSearch.pop();

			for (int i=0; i<nodeCount; ++i) {
				int edgeWeight = edges.at(current).at(i);
				if (edgeWeight != -1) {
					//for each node connected to current
					if (nodeDistance[i] == -1) {
						nodeDistance[i] = nodeDistance[current] + edgeWeight;
						nodesToSearch.emplace(i);
					}
				}
			}
		}
		vector<int> results;
		results.reserve(nodeCount);
		for (auto i : nodeDistance) {
			results.emplace_back(i.second);
		}
		return results;
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
		cout << endl;
	}
	return 0;
}
