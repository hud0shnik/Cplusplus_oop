#include <iostream>
#include <list>
#include <iterator>
#include <complex>
using namespace std;

template <class T>
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

template <class T>
void pop(list <T>& lst, T element) {
	lst.remove(element);
}

template <class T>
bool P(T element) {
	if (real(element) < 0) {
		return true;
	}
	return false;
}

template <class T>
list <T> filter(list <T>& lst, bool(*ptr)(T)) {
	list <complex <int>> son;
	auto it = lst.begin();
	while (it != lst.end()) {
		if (P(*it)) {
			son.push_back(*it);
		}
		*it++;
	}
	return son;
}

template <class program>
void print(list <program>& father) {
	auto it = father.begin();
	for (; it != father.end(); ++it) {
		cout << *it;
	}
}

class program {
private:
	int Price;
	int Version;
	string Name;
	string License;
	string Dev;
	string Language;

public:
	program() {
		Price = 0;
		Version = 0;
		Name = "";
	}

	program(int price, int version, string name, string license, string dev, string language) {
		Price = price;
		Version = version;
		Name = name;
		License = license;
		Dev = dev;
		Language = language;
	}
	program(int Price, int version, string name) {
		Price = Price;
		Version = version;
		Name = name;
	}

	bool operator > (program& L) {
		bool res = false;
		if (Price > L.Price)
			res = true;
		else if (Price == L.Price)
			if (Version > L.Version)
				res = true;
			else if (Version == L.Version)
				if (Name > L.Name)
					res = true;
				else if (Name == L.Name)
					if (License > L.License)
						res = true;
					else if (License == L.License)
						cout << "programs match";
		return res;
	}

	bool operator == (program& L) {
		if ((Price == L.Price) & (Version == L.Version) & (Name == L.Name) & (License == L.License))
			return true;
		else
			return false;
	}

	friend ostream& operator <<(ostream& ustream,
		const program& obj);
};

template <class T>
T pop(list <T>& lst, int position = 0) {
	typename list <T> ::iterator p = lst.begin();
	advance(p, position);
	T value(*p);
	lst.erase(p);
	return value;
}

ostream& operator <<(ostream& ustream,
	const program& obj) {
	ustream << "Price: " << obj.Price << " Version: " << obj.Version <<
		" Name: " << obj.Name;
	ustream << endl;

	return ustream;
}

template <class program>
void bubble(list <program>& father) {
	auto it = father.begin();
	auto it1 = father.begin();
	auto it2 = ++it1;
	for (; it != father.end(); ++it) {
		for (; it2 != (father.end()--); ++it2) {
			if (*it > *it2)
				swap(*it, *it2);
		}
	}
}

int main() {

	program first(99, 28, "Johny");
	program second(13, 28, "Arnold");
	program third(403, 18, "Sanya");

	list <program> example;
	example.push_back(first);
	example.push_back(second);
	example.push_back(third);

	print(example);

	bubble(example);

	print(example);
	cout << endl;

	cout << pop(example) << endl;

	print(example);

	return 0;
}