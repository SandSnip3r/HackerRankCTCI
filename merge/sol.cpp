#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <iostream>
#include <vector>

namespace MergeSort {

	template <class BidirIt, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::reverse_iterator requires the passed iterator to be an BidirectionalIterator
	BidirIt reverseIt(std::reverse_iterator<BidirIt> it) {
		return it.base();
	}

	template <class BidirIt, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::reverse_iterator requires the passed iterator to be an BidirectionalIterator
	std::reverse_iterator<BidirIt> reverseIt(BidirIt it) {
		return std::reverse_iterator<BidirIt>(it);
	}

	template<class Compare>
	struct ReversedCompare {
		Compare compare;
		template<class Left, class Right>
		bool operator()(const Left& left, const Right& right) {
			return compare(right,left);
		}
	};

	template <class Compare>
	Compare reverseComp(ReversedCompare<Compare> compare) {
		return compare.compare;
	}

	template <class Compare>
	ReversedCompare<Compare> reverseComp(Compare compare) {
		return ReversedCompare<Compare>{compare};
	}

	template<class LeftInputIt, class RightInputIt, class OutputIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<LeftInputIt>::iterator_category>::value
																																																					&& std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<RightInputIt>::iterator_category>::value
																																																					/*&& std::is_base_of<std::output_iterator_tag, typename std::iterator_traits<OutputIt>::iterator_category>::value*/>>
	//std::move requires the passed iterators to be an InputIterator and OutputIterator
	long long mergeInto(LeftInputIt leftIt, LeftInputIt leftEnd, RightInputIt rightIt, RightInputIt rightEnd, OutputIt insertIt, Compare Comp) {
		LeftInputIt leftBegin{leftIt};
		RightInputIt rightBegin{rightIt};
		OutputIt outputBegin{insertIt};

		long long swapCount = 0;
		//Begin merging
		while (leftIt != leftEnd && rightIt != rightEnd) {
			//While there are elements in both lists
			auto leftValue = *leftIt;
			auto rightValue = *rightIt;

			if (!Comp(rightValue, leftValue)) {
				//Left list's first element is inserted
				*insertIt = leftValue;
				++leftIt;
			} else {
				//Right list's first element is inserted
				swapCount += std::distance(leftBegin, leftEnd) + std::distance(rightBegin, rightIt) - std::distance(outputBegin, insertIt);
				*insertIt = rightValue;
				++rightIt;
			}
			++insertIt;
		}
		//Now at least one list is empty
		if (leftIt != leftEnd) {
			//Insert all of the left list into the list (right is empty)
			std::move(leftIt, leftEnd, insertIt);
		} else if (rightIt != rightEnd) {
			//Insert all of the right list into the list (left is empty)
			std::move(rightIt, rightEnd, insertIt);
		}
		return swapCount;
	}

	template<class BidirIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::distance requires the passed iterator to be an InputIterator
	//std::upper_bound requires the passed iterator to be an ForwardIterator
	//std::prev and reverseIt require the passed iterator to be an BidirectionalIterator
	long long merge(BidirIt begin, BidirIt middle, BidirIt end, Compare Comp) {
		size_t leftLength = std::distance(begin, middle);
		size_t rightLength = std::distance(middle, end);

		if (leftLength > rightLength) {
			//Left list is bigger, swap everything around and recursively call this function
			return merge(reverseIt(end), reverseIt(middle), reverseIt(begin), reverseComp(Comp));
		}
		//Now guaranteed that [begin,middle) <= [middle,end)

		//Determine if there are any leftmost positions that are already in place
		auto newLeftBegin = std::upper_bound(begin, middle, *middle, Comp);
		if (newLeftBegin == middle) {
			//Everything in the left list is smaller than the first in the right list, we're done
			return 0;
		}
		//Determine if there are any righmost positions that are already in place
		auto rightEnd = std::upper_bound(middle, end, *(std::prev(middle)), Comp);
		if (rightEnd == middle) {
			//Everything in the left list is smaller than the first in the right list, we're done
			return 0;
		}
		//	"These preliminary searches[newLeftBegin&rightEnd] may not pay off, and can be expected *not* to
		//	repay their cost if the data is random.  But they can win huge in all of
		//	time, copying, and memory savings when they do pay"
		//	According to https://svn.python.org/projects/python/trunk/Objects/listsort.txt

		// newLeftBegin saved std::distance(begin, newLeftBegin)*sizeof(BidirIt) bytes of extra space usage
		// rightEnd saved std::distance(rightEnd, end)*sizeof(BidirIt) bytes of extra space usage
		//Save the left list in a temp because we'll be overwriting it as we insert
		using ValueType = typename std::iterator_traits<BidirIt>::value_type;
		std::vector<ValueType> tempList(newLeftBegin, middle);
		auto leftIt = tempList.begin();
		auto leftEnd = tempList.end();

		auto rightIt = middle;

		auto insertIt = newLeftBegin;

		return mergeInto(leftIt, leftEnd, rightIt, rightEnd, insertIt, Comp);
	}

	template<class BidirIt, class Compare = std::less<>, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::distance and std::next require the passed iterator to be an InputIterator
	//merge requires the passed iterator to be an BidirectionalIterator
	long long sort(BidirIt begin, BidirIt end, Compare Comp = Compare()) {
		size_t length = std::distance(begin,end);
		long long swapCount = 0;

		//Bottom-up merge algorithm
		for (size_t width=1; width<length; width*=2) {
			//We are going to merge lists of length 'width'
			for (size_t listStart=0; listStart<length; listStart+=(width*2)) {
				//These 2 lists are [listStart, listStart+width) and [listStart+width, listStart+(width*2))
				size_t firstPos = listStart;
				size_t middlePos = listStart+width;
				size_t endPos = listStart+(width*2);
				if (middlePos >= length) {
					middlePos = length;
					endPos = length;
				} else if (endPos >= length) {
					endPos = length;
				}
				swapCount += merge(std::next(begin, firstPos), std::next(begin, middlePos), std::next(begin, endPos), Comp);
			}
		}
		return swapCount;
	}
} //namespace MergeSort

using namespace std;

void readAndSolveProblem();

int main() {
	int numberOfDatasets;
	cin >> numberOfDatasets;
	for (int i=0; i<numberOfDatasets; ++i) {
		readAndSolveProblem();
	}
	return 0;
}

void readAndSolveProblem() {
	int numberOfElements;
	cin >> numberOfElements;
	vector<int> nums;
	nums.reserve(numberOfElements);
	for (int i=0; i<numberOfElements; ++i) {
		int temp;
		cin >> temp;
		nums.emplace_back(temp);
	}
	cout << MergeSort::sort(nums.begin(), nums.end()) << '\n';
}