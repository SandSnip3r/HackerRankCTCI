#include <cmath>
#include <iostream>
#include <map>

using namespace std;

int calculatePossibilities(int staircaseHeight);

int main() {
	int numberOfStaircases;
	cin >> numberOfStaircases;
	while (numberOfStaircases > 0) {
		int staircaseHeight;
		cin >> staircaseHeight;
		int possibilities = calculatePossibilities(staircaseHeight);
		cout << possibilities << '\n';
		--numberOfStaircases;
	}
	return 0;
}

int calculatePossibilities(int staircaseHeight) {
	static map<int,int> previouslyComputedSolutions;
	if (staircaseHeight == 0) {
		//The case where we've stepped to the end is a single possibility
		return 1;
	}
	if (staircaseHeight == 1) {
		//The case where there is 1 step is a single possibility
		return 1;
	}
	if (staircaseHeight == 2) {
		//The case where there are 2 steps has 2 possibilities
		return 2;
	}
	if (previouslyComputedSolutions.count(staircaseHeight) != 0) {
		return previouslyComputedSolutions[staircaseHeight];
	}
	int sum=0;
	//Take 1 step, then calculate remaining
	sum += calculatePossibilities(staircaseHeight-1);
	//Take 2 steps, then calculate remaining
	sum += calculatePossibilities(staircaseHeight-2);
	//Take 3 steps, then calculate remaining
	sum += calculatePossibilities(staircaseHeight-3);
	previouslyComputedSolutions[staircaseHeight] = sum;
	return sum;
}