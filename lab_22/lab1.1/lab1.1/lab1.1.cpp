#include <iostream>
#include <ctype.h>
#include <iterator>
#include <list>
using namespace std;


void print(list <char>& listOfLetters) {
	for (auto it = listOfLetters.begin(); it != listOfLetters.end(); *it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void pop(list <char>& listOfLetters, char letter) {
	listOfLetters.remove(letter);
}

bool predicate(char letter) {
	if (islower(letter)) {
		return true;
	}
	return false;
}
void push(list <char>& listOfLetters, char letter) {
	auto it = listOfLetters.begin();
	while ((it != listOfLetters.end()) && (letter > *it)) {
		*it++;
	}
	if (it != listOfLetters.end())
		listOfLetters.insert(it, letter);
	else
		listOfLetters.push_back(letter);
}
list <char> filter(list <char>& listOfLetters, bool(*ptr)(char)) {
	list <char> newListOfLetters;
	auto it = listOfLetters.begin();
	while (it != listOfLetters.end()) {
		if (predicate(*it)) {
			newListOfLetters.push_back(*it);
		}
		*it++;
	}
	return newListOfLetters;
}


int main() {
	list <char> listOfLetters, newListOfLetters;

	listOfLetters.push_back('I');
	listOfLetters.push_back('L');
	listOfLetters.push_back('O');
	listOfLetters.push_back('V');
	listOfLetters.push_back('E');
	listOfLetters.push_back('c');
	listOfLetters.push_back('o');
	listOfLetters.push_back('d');
	listOfLetters.push_back('i');
	listOfLetters.push_back('n');
	listOfLetters.push_back('g');
	cout << "Before push" << endl;
	print(listOfLetters);

	push(listOfLetters, 'a');
	push(listOfLetters, 'b');
	push(listOfLetters, 'C');
	push(listOfLetters, 'D');
	cout << "After push" << endl;
	print(listOfLetters);

	cout << "After pop" << endl;
	pop(listOfLetters, 'a');
	print(listOfLetters);

	bool(*ptr)(char);
	ptr = predicate;
	newListOfLetters = filter(listOfLetters, ptr);
	cout << "\n";

	cout << "After filter" << endl;
	print(newListOfLetters);
	return 0;
}