#include <iostream>

using namespace std;

int main() {
	int numberCount;
	cin >> numberCount;
	int result=0;
	for (int i=0; i<numberCount; ++i) {
		int num;
		cin >> num;
		result ^= num;
	}
	cout << result << '\n';
	return 0;
}