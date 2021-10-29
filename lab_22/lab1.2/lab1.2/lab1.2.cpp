#include <iostream>
#include <list>
#include <iterator>
#include <complex>
using namespace std;

template <class T>
void push(list <T>& lst, T son) {
	auto it = lst.begin();
	while ((it != lst.end()) && (son > *it)) {
		*it++;
	}

	if (it != lst.end())
		lst.insert(it, son);
	else
		lst.push_back(son);
}

template <class T>
void pop(list <T>& lst, T son) {
	lst.remove(son);
}

template <class T>
bool predikant(T son) {
	if (real(son) < 0) {
		return true;
	}
	return false;
}

template <class T>
list <T> filter(list <T>& lst, bool(*ptr)(T)) {
	list <complex <int>> son;
	auto it = lst.begin();
	while (it != lst.end()) {
		if (predikant(*it)) {
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
		License = "";
		Dev = "";
		Language = "";
	}

	program(int price, int version, string name, string license, string dev, string language) {
		Price = price;
		Version = version;
		Name = name;
		License = license;
		Dev = dev;
		Language = language;
	}
	program(int price, int version, string name) {
		Price = price;
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
		if ((Price == L.Price) & (Version == L.Version) & (Name == L.Name) & (License == L.License) & (Dev == L.Dev) & (Language == L.Language))
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
	ustream << "Price " << obj.Price << " Version " << obj.Version <<
		" Name " << obj.Name << " ";
	ustream << endl;

	return ustream;
}

template <class program>
void sort(list <program>& father) {
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
	list <program> progList;
	program prog1(777, 1337, "Abobe Photoshop");
	program prog2(-0, 47, "Hearth$$$tone");
	program prog3(-666, 418, "viSuAlStUdIO 2010 <3 ");

	progList.push_back(prog1);
	progList.push_back(prog2);
	progList.push_back(prog3);

	print(progList);

	sort(progList);

	print(progList);
	cout << endl;

	cout << pop(progList) << endl;

	print(progList);

	return 0;
}