#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
	string strA, strB;
	cin >> strA >> strB;
	map<char,int> charCounts;
	for (char c='a'; c<='z'; ++c) {
		charCounts[c] = 0;
	}
	for (char c : strA) {
		++charCounts[c];
	}
	for (char c : strB) {
		--charCounts[c];
	}
	int sum=0;
	for (const auto &p : charCounts) {
		sum += abs(p.second);
	}
	cout << sum << '\n';
	return 0;
}