#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void populateCharCounts(const string &str, vector<int> &charCounts);

int main() {
	string strA, strB;
	cin >> strA >> strB;
	vector<int> charCountsA(26,0);
	vector<int> charCountsB(26,0);
	populateCharCounts(strA, charCountsA);
	populateCharCounts(strB, charCountsB);
	int sum=0;
	for (int i=0; i<26; ++i) {
		sum += abs(charCountsA.at(i)-charCountsB.at(i));
	}
	cout << sum << '\n';
	return 0;
}

void populateCharCounts(const string &str, vector<int> &charCounts) {
	for (char c : str) {
		++charCounts[c-'a'];
	}
}