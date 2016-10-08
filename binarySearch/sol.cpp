#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Flavor {
public:
	int cost, index;
	Flavor(int c, int i) : cost(c), index(i) {}
};

bool operator<(const Flavor &left, const Flavor &right) {
	return left.cost < right.cost;
}

pair<int,int> getFlavorPair(int wallet, const vector<Flavor> &flavors);

template<typename T>
void sortPair(std::pair<T,T> &p) {
	if (!(p.first < p.second)) {
		std::swap(p.first, p.second);
	}
}

int main() {
	int tripCount;
	cin >> tripCount;
	for (int i=0; i<tripCount; ++i) {
		int wallet, flavorCount;
		cin >> wallet >> flavorCount;
		vector<Flavor> flavors;
		for (int j=0; j<flavorCount; ++j) {
			int cost;
			cin >> cost;
			flavors.emplace_back(cost, j+1);
		}
		std::sort(flavors.begin(), flavors.end());
		auto flavorIndexPair = getFlavorPair(wallet, flavors);
		sortPair(flavorIndexPair);
		cout << flavorIndexPair.first << ' ' << flavorIndexPair.second << '\n';
	}
	return 0;
}

pair<int,int> getFlavorPair(int wallet, const vector<Flavor> &flavors) {
	for (int i=0; i<flavors.size(); ++i) {
		int otherAmount = wallet - flavors[i].cost;
		if (otherAmount > 0) {
			auto it = std::lower_bound(flavors.begin()+i+1, flavors.end(), Flavor{otherAmount,0});
			if (it->cost == otherAmount) {
				return {flavors[i].index, it->index};
			}
		}
	}
	return {0,0};
}