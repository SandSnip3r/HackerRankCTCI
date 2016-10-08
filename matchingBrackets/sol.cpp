#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

bool allBracketsMatch(const string &input);

int main() {
	int numOfTests;
	cin >> numOfTests;
	while (numOfTests > 0) {
		string input;
		cin >> input;
		if (allBracketsMatch(input)) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
		--numOfTests;
	}
	return 0;
}

bool allBracketsMatch(const string &input) {
	static const unordered_map<char,char> matchingBracketMap{{')', '('}, {']', '['}, {'}', '{'}};
	stack<char> bracketStack;
	char temp;
	for (char c : input) {
		switch (c) {
			case '(':
			case '[':
			case '{':
				bracketStack.push(c);
				break;
			case ')':
			case ']':
			case '}':
				if (bracketStack.empty()) {
					return false;
				}
				temp = bracketStack.top();
				if (temp != matchingBracketMap.at(c)) {
					return false;
				} else {
					bracketStack.pop();
				}
				break;
		}
	}
	return bracketStack.empty();
}