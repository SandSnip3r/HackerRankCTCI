#include <iostream>

using namespace std;

int main() {
	int numOfElements;
	cin >> numOfElements;
	int arr[numOfElements];
	for (int i=0; i<numOfElements; ++i) {
		cin >> arr[i];
	}

	int totalNumberOfSwaps=0;

	for (int i = 0; i < numOfElements; i++) {
		// Track number of elements swapped during a single array traversal
		int numberOfSwaps = 0;

		for (int j = 0; j < numOfElements - 1; j++) {
			// Swap adjacent elements if they are in decreasing order
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				numberOfSwaps++;
				++totalNumberOfSwaps;
			}
		}

		// If no elements were swapped during a traversal, array is sorted
		if (numberOfSwaps == 0) {
			break;
		}
	}

	cout << "Array is sorted in " << totalNumberOfSwaps << " swaps.\n";
	cout << "First Element: " << arr[0] << '\n';
	cout << "Last Element: " << arr[numOfElements-1] << '\n';
	return 0;
}