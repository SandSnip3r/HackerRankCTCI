#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename Type, typename Compare = std::less<>>
class Heap {
private:
	vector<Type> arr;
	Compare comp{Compare()};

	bool hasLeftChild(size_t index) {
		return getLeftChildIndex(index) < arr.size();
	}

	bool hasRightChild(size_t index) {
		return (getLeftChildIndex(index)+1) < arr.size();
	}

	size_t getLeftChildIndex(size_t index) {
		return index * 2 + 1;
	}

	void heapifyDown() {
		size_t index=0;
		while (hasLeftChild(index)) {
			auto maxChildIndex = getLeftChildIndex(index);
			if (hasRightChild(index)) {
				if (comp(arr.at(maxChildIndex), arr.at(maxChildIndex+1))) {
					//If right child is bigger than left
					++maxChildIndex;
				}
			}
			if (comp(arr.at(index), arr.at(maxChildIndex))) {
				//need to swap down
				std::iter_swap(arr.begin()+index, arr.begin()+maxChildIndex);
				index = maxChildIndex;
			} else {
				//Proper order
				break;
			}
		}
	}

	void heapifyUp() {
		size_t index = arr.size()-1;
		while (index > 0) {
			auto parentIndex = (index-1) / 2;
			if (comp(arr.at(index), arr.at(parentIndex))) {
				//Max heap order satisfied, done
				break;
			} else {
				std::iter_swap(arr.begin()+index, arr.begin()+parentIndex);
				index = parentIndex;
			}
		}
	}
public:
	void reserve(size_t newSize) {
		arr.reserve(newSize);
	}

	Type top() const {
		if (arr.empty()) {
			throw std::runtime_error("Heap::top but empty");
		}
		return arr[0];
	}

	void pop() {
		if (arr.empty()) {
			throw std::runtime_error("Heap::pop but empty");
		}
		//Swap first and last element
		std::iter_swap(arr.begin(), std::prev(arr.end()));
		//Erase last
		arr.erase(std::prev(arr.end()));
		heapifyDown();
	}

	void insert(const Type &newData) {
		arr.push_back(newData);
		heapifyUp();
	}

	bool empty() const {
		return arr.empty();
	}

	size_t size() const {
		return arr.size();
	}

	void print() const {
		cout << "Heap: ";
		for (auto i : arr) {
			cout << i << ' ';
		}
		cout << '\n';
	}
};

template<typename T>
using MinHeap = Heap<T, std::greater<T>>;

template<typename T>
using MaxHeap = Heap<T, std::less<T>>;

void balanceHeaps(MinHeap<int> &minHeap, MaxHeap<int> &maxHeap);
void printMedian(MinHeap<int> &minHeap, MaxHeap<int> &maxHeap);

int main() {
	int inputSize;
	cin >> inputSize;
	MinHeap<int> minHeap;
	MaxHeap<int> maxHeap;
	for (int i=0; i<inputSize; ++i) {
		int num;
		cin >> num;
		if (i % 2 == 0) {
			minHeap.insert(num);
		} else {
			maxHeap.insert(num);
		}
		balanceHeaps(minHeap, maxHeap);
		printMedian(minHeap, maxHeap);
	}
	return 0;
}

void balanceHeaps(MinHeap<int> &minHeap, MaxHeap<int> &maxHeap) {
	if (minHeap.empty() || maxHeap.empty()) {
		return;
	}
	int maxTop = maxHeap.top();
	int minTop = minHeap.top();
	if (maxTop > minTop) {
		minHeap.pop();
		maxHeap.pop();
		minHeap.insert(maxTop);
		maxHeap.insert(minTop);
	}
}

void printMedian(MinHeap<int> &minHeap, MaxHeap<int> &maxHeap) {
	float result;
	if (minHeap.size() > maxHeap.size()) {
		result = minHeap.top();
	} else if (minHeap.size() < maxHeap.size()) {
		result = maxHeap.top();
	} else {
		result = (maxHeap.top() + minHeap.top()) / 2.0;
	}
	printf("%.1f\n", result);
}