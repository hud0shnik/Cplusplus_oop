#include <iostream>
#include <ctype.h>
#include <iterator>
#include <list>
using namespace std;


void print(list < char >& llist) {
	for (auto it = llist.begin(); it != llist.end(); *it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void pop(list < char>& llist, char ch) {
	llist.remove(ch);
}

bool predikant(char ch) {
	if (islower(ch)) {
		return true;
	}
	return false;
}
void push(list < char>& llist, char ch) {
	auto it = llist.begin();
	while ((it != llist.end()) && (ch > *it)) {
		*it++;
	}
	if (it != llist.end())
		llist.insert(it, ch);
	else
		llist.push_back(ch);
}
list < char > filter(list < char >& llist, bool(*ptr)(char)) {
	list < char > son;
	auto it = llist.begin();
	while (it != llist.end()) {
		if (predikant(*it)) {
			son.push_back(*it);
		}
		*it++;
	}
	return son;
}


int main() {
	list < char> llist, llist2;

	llist.push_back('U');
	llist.push_back('S');
	llist.push_back('S');
	llist.push_back('R');
	llist.push_back('U');
	llist.push_back('w');
	llist.push_back('u');
	llist.push_back('o');
	llist.push_back('w');
	llist.push_back('O');
	cout << "Before push: " << endl;
	print(llist);

	push(llist, 'a');
	push(llist, 'b');
	push(llist, 'O');
	push(llist, 'B');
	cout << "After push: " << endl;
	print(llist);

	cout << "After pop: " << endl;
	pop(llist, 'a');
	print(llist);

	bool(*ptr)(char);
	ptr = predikant;
	llist2 = filter(llist, ptr);
	cout << "\n";

	cout << "After filter: " << endl;
	print(llist2);
	cout << "That's all! UwU" << endl;
	return 0;
}