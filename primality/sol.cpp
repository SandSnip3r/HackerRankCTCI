#include <cmath>
#include <iostream>

using namespace std;

bool isPrime(int num);

int main() {
	int numberCount;
	cin >> numberCount;
	while (numberCount > 0) {
		int num;
		cin >> num;
		if (isPrime(num)) {
			cout << "Prime\n";
		} else {
			cout << "Not prime\n";
		}
		--numberCount;
	}
	return 0;
}

bool isPrime(int num) {
	if (num < 2) {
		return false;
	}
	if (num < 4) {
		return true;
	}
	if (num % 2 == 0) {
		return false;
	}
	for (int i=3, sqRoot=sqrt(num); i<=sqRoot; i+=2) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}