#include <iostream>
#include <vector>

using namespace std;

int main() {
	int dollarAmount, denominationCount;
	cin >> dollarAmount >> denominationCount;
	vector<int> denoms(denominationCount);
	for (int i=0; i<denominationCount; ++i) {
		cin >> denoms[i];
	}

	vector<long long> possibilities(dollarAmount+1, 0);
	possibilities[0] = 1;
	for (int denom: denoms) {
		for (auto i=denom; i<=dollarAmount; ++ i) {
			possibilities[i] += possibilities[i-denom];
		}
	}
	cout << possibilities[dollarAmount] << '\n';
	return 0;
}