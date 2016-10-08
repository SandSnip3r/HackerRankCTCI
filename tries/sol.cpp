#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Trie {
private:
	class Node {
	public:
		bool isComplete{false};
		char data{0};
		int count{0};
		unordered_map<char,Node*> nexts;
		Node() = default;
		Node(char c) : data(c) {}
		~Node() {
			for (auto &i : nexts) {
				delete i.second;
			}
		}
	};
	Node root;
public:
	void insert(const string &str) {
		if (str.empty()) {
			return;
		}
		Node *ptr{&root};
		for (char c : str) {
			if (ptr->nexts.find(c) == ptr->nexts.end()) {
				//Char doesnt exist
				ptr->nexts.emplace(c, new Node(c));
				ptr = ptr->nexts.at(c);
			} else {
				//Char does exist
				ptr = ptr->nexts.at(c);
			}
			++ptr->count;
		}
		ptr->isComplete = true;
	}
	int count(const string &str) {
		Node *ptr{&root};
		for (char c : str) {
			if (ptr->nexts.find(c) == ptr->nexts.end()) {
				return 0;
			} else {
				ptr = ptr->nexts.at(c);
			}
		}
		return ptr->count;
	}
};

int main() {
	int operationCount;
	cin >> operationCount;

	Trie contactTrie;

	for (int i=0; i<operationCount; ++i) {
		string operation, contact;
		cin >> operation >> contact;
		if (operation == "add") {
			contactTrie.insert(contact);
		} else if (operation == "find") {
			cout << contactTrie.count(contact) << '\n';
		}
	}
	return 0;
}