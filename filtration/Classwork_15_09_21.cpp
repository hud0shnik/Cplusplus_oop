#include <iostream>
#include <list>
using namespace std;

template<class T>
void push(list<T>& lst, T element)
{
	auto it = lst.begin();

	while ((it != lst.end()) && (element > *it))
	{
		*it++;
	}

	if (it != lst.end())
		lst.insert(it, element);
	else
		lst.push_back(element);
}

template<class T>
list<T> filter(list<T> Source, bool(*p)(T))
{
	list<int> result;
	list<int>::iterator it = Source.begin();
	while (it != Source.end()) {
		if (p(*it)) {
			result.push_back(*it);
		}
		*it++;
	}
	return result;
}

bool filtration(int a) {
	if (a % 2== 0) {
		return true;
	}
	return false;
}

int main() {
	list<int> lst, lst2;
	for (int i = 0; i < 10; i += 2) {
		lst.push_back(i);
	}
	push(lst, -5);
	list<int>::iterator it = lst.begin();
	while (it != lst.end()) {
		std::cout << *it << " ";
		*it++;
	}
	bool (*ptr)(int); ptr = filtration;
	lst2 = filter(lst, ptr);
	it = lst2.begin();
	cout << "\n";
	/*-=-=--=-=-*/
	 it = lst2.begin();
	while (it!=lst2.end())
	{
		std::cout << *it << " ";
		*it++;
	}
}