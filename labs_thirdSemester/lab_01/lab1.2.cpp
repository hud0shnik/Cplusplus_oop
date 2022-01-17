#include <iostream>
#include <list>
#include <iterator>
using namespace std;

template <class T>
void push(list <T>& lst, T element) {
	auto i = lst.begin();
	while ((i != lst.end()) && (element > *i)) {
		*i++;
	}

	if (i != lst.end())
		lst.insert(i, element);
	else
		lst.push_back(element);
}

template <class T>
void pop(list <T>& lst, T element) {
	lst.remove(element);
}

template<class T>
bool P(T element) {
	return ((element >= 'A') && (element <= 'Z'));
}

template <class T>
list <T> filter(list <T>& lst, bool(*ptr)(T)) {
	list <T> son;
	auto i = lst.begin();
	while (i != lst.end()) {
		if (P(*i)) {
			son.push_back(*i);
		}
		*i++;
	}
	return son;
}

template <class realestate>
void print(list <realestate>& father) {
	auto i = father.begin();
	for (; i != father.end(); ++i) {
		cout << *i;
	}
}

enum type {
	Gorodskoy_dom,
	Zagorodny_dom,
	Kvartira,
	Dacha,
};

class realestate {
private:
	int S1;
	int S2;
	string Adress;
	string Price;
	type Type;

public:
	realestate() {
		S1 = 0;
		S2 = 0;
		Adress = "";
		Price = "";
		Type = Gorodskoy_dom;
	}

	realestate(int S1, int S2, string Adress, string Price, string citizenship, string Type) {
		S1 = S1;
		S2 = S2;
		Adress = Adress;
		Price = Price;
		Type = Type;
	}

	realestate(int S1, int S2, string Adress) {
		S1 = S1;
		S2 = S2;
		Adress = Adress;
	}

	bool operator > (realestate& L) {
		bool res = false;
		if (S1 > L.S1)
			res = true;
		else if (S1 == L.S1)
			if (S2 > L.S2)
				res = true;
			else if (S2 == L.S2)
				if (Adress > L.Adress)
					res = true;
				else if (Adress == L.Adress)
					if (Price > L.Price)
						res = true;
					else if (Price == L.Price)
						cout << "error";
		return res;
	}

	bool operator == (realestate& L) {
		if ((S1 == L.S1) & (S2 == L.S2) & (Adress == L.Adress) & (Price == L.Price))
			return true;
		else
			return false;
	}

	friend ostream& operator <<(ostream& result, const realestate& obj);
};

template <class T>
T pop(list <T>& lst, int position = 0) {
	typename list <T>::iterator p = lst.begin();
	advance(p, position);
	T value(*p);
	lst.erase(p);
	return value;
}

ostream& operator <<(ostream& result, const realestate& obj) {
	if (obj.Price == "" & obj.Type == Gorodskoy_dom) {
		result << "S1: " << obj.S1 << " S2: " << obj.S2 <<
			" Adress: " << obj.Adress;
		result << endl;
	}
	else {
		result << "S1: " << obj.S1 << " S2: " << obj.S2 <<
			" Adress: " << obj.Adress << " Price: " << obj.Price << " Type: " << obj.Type;
		result << endl;
	}

	return result;
}

template <class realestate>
void bubble(list <realestate>& father) {
	auto i = father.begin();
	auto i1 = father.begin();
	auto i2 = ++i1;
	for (; i != father.end(); ++i) {
		for (; i2 != (father.end()--); ++i2) {
			if (*i > *i2)
				swap(*i, *i2);
		}
	}
}

int main() {
	return 0;
}