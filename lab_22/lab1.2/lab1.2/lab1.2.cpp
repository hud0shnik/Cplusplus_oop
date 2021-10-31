#include <iostream>
#include <list>
#include <iterator>
using namespace std;

template <class T>
void push(list <T>& listOfLetters, T son) {
	auto it = listOfLetters.begin();
	while ((it != listOfLetters.end()) && (son > *it)) {
		*it++;
	}

	if (it != listOfLetters.end())
		listOfLetters.insert(it, son);
	else
		listOfLetters.push_back(son);
}

template <class T>
void pop(list <T>& listOfLetters, T son) {
	listOfLetters.remove(son);
}

bool predicate(char letter) {
	if (islower(letter)) {
		return true;
	}
	else {
		return false;
	}
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

	bool operator > (program& info) {
		bool result = false;
		if (Price > info.Price)
			result = true;
		else if (Price == info.Price)
			if (Version > info.Version)
				result = true;
			else if (Version == info.Version)
				if (Name > info.Name)
					result = true;
				else if (Name == info.Name)
					if (License > info.License)
						result = true;
					else if (License == info.License)
						cout << "Programs match";
		return result;
	}

	bool operator == (program& info) {
		if ((Price == info.Price) & (Version == info.Version) & (Name == info.Name)
			& (License == info.License) & (Dev == info.Dev) & (Language == info.Language))
			return true;
		else
			return false;
	}

	friend ostream& operator <<(ostream& ustream,
		const program& obj);
};

template <class T>
T pop(list <T>& listOfLetters, int position = 0) {
	typename list <T> ::iterator p = listOfLetters.begin();
	advance(p, position);
	T value(*p);
	listOfLetters.erase(p);
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
	auto firstIt = father.begin();
	auto thirdIt = father.begin();
	auto secondIt = ++thirdIt;
	for (; firstIt != father.end(); ++firstIt) {
		for (; secondIt != (father.end()--); ++secondIt) {
			if (*firstIt > *secondIt)
				swap(*firstIt, *secondIt);
		}
	}
}

int main() {
	list <program> listOfNames;
	program firstName(5000, 13, "Valorant");
	program secondName(-0, 145, "Minecraft");
	program thirdName(-1234, 123, "World of Warcraft");

	listOfNames.push_back(firstName);
	listOfNames.push_back(secondName);
	listOfNames.push_back(thirdName);

	print(listOfNames);

	sort(listOfNames);

	print(listOfNames);
	cout << endl;

	cout << pop(listOfNames) << endl;

	print(listOfNames);

	return 0;
}