#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
	int numberOfElements, rotationCount;
	cin >> numberOfElements >> rotationCount;
	vector<int> myNums;
	myNums.reserve(numberOfElements);
	for (int i=0; i<numberOfElements; ++i) {
		int temp;
		cin >> temp;
		myNums.emplace_back(temp);
	}
	rotate(myNums.begin(), myNums.begin()+rotationCount, myNums.end());
	copy(myNums.begin(), myNums.end(), ostream_iterator<int>(cout, " "));
	cout << '\n';
	return 0;
}