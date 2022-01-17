#include <iostream>
#include <list>
#include <iterator>
using namespace std;

template<class T>
void push(list <T>& lst, T element) {
	auto it = lst.begin();
	while ((it != lst.end()) && (element > *it)) {
		*it++;
	}
	if (it != lst.end())
		lst.insert(it, element);
	else
		lst.push_back(element);
}

template<class T>
T pop(list<T>& father) {
	T temp = father.front();
	father.pop_front();
	return temp;
}

template<class T>
bool P(T element) {
	return ((element >= 'A') && (element <= 'Z'));
}

template<class T>
list <T> filter(list <T >& lst, bool(*ptr)(T)) {
	list<T> son;
	auto it = lst.begin();
	while (it != lst.end()) {
		if (P(*it)) {
			son.push_back(*it);
		}
		*it++;
	}
	return son;
}

template<class T>
void print(list <T>& lst) {
	for (auto it = lst.begin(); it != lst.end(); *it++) {
		cout << *it << " ";
	}
	cout << endl;
}

int main() {
	return 0;
}