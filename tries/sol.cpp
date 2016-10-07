#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Trie {
private:
	class Node {
	public:
		bool isComplete{false};
		char data{0};
		unordered_map<char,Node*> nexts;
		Node() = default;
		Node(string::const_iterator strBegin, string::const_iterator strEnd) : data(*strBegin) {
			++strBegin;
			if (strBegin != strEnd) {
				nexts.emplace(*strBegin, new Node(strBegin, strEnd));
			} else {
				isComplete = true;
			}
		}
	};
	Node root;
	void print(Node *ptr) {
		cout << ptr->data << (ptr->isComplete ? "* " : " ");
		if (!ptr->nexts.empty()) {
			cout << '[';
			for (const auto &i : ptr->nexts) {
				print(i.second);
			}
			cout << ']';
		}
	}
	int getChildrenCount(Node *ptr) {
		int sum = 0;
		if (ptr->isComplete) {
			++sum;
		}
		for (const auto &i : ptr->nexts) {
			sum += getChildrenCount(i.second);
		}
		return sum;
	}
public:
	void insert(const string &str) {
		if (str.empty()) {
			return;
		}
		if (root.nexts.count(str[0]) == 0) {
			//This char doesnt exist at the root yet
			root.nexts.emplace(str[0], new Node(str.begin(), str.end()));
		} else {
			//This char exists at the root
			Node *ptr{root.nexts.at(str[0])};
			for (auto it=std::next(str.cbegin()), end=str.cend(); it!=end; ++it) {
				if (ptr->nexts.count(*it) == 0) {
					//Char doesnt exist at this point
					ptr->nexts.emplace(*it, new Node(it, end));
					break;
				} else {
					//Char exists at this point
					ptr = ptr->nexts.at(*it);
				}
			}
		}
	}
	void print() {
		cout << "Trie: ";
		print(&root);
		cout << '\n';
	}
	int count(const string &str) {
		Node *ptr{&root};
		for (char c : str) {
			if (ptr->nexts.count(c) == 0) {
				return 0;
			} else {
				ptr = ptr->nexts.at(c);
			}
		}
		return getChildrenCount(ptr);
	}
};

int main() {
	int operationCount;
	cin >> operationCount;

	Trie contactTrie;

	for (int i=0; i<operationCount; ++i) {
		string operation, contact;
		cin >> operation >> contact;
		// cout << "User wants to " << operation << ' ' << contact << '\n';
		if (operation == "add") {
			contactTrie.insert(contact);
			// contactTrie.print();
		} else if (operation == "find") {
			cout << contactTrie.count(contact) << '\n';
		} else {
			throw runtime_error("Unknown operation \""+operation+"\"");
		}
	}
	return 0;
}