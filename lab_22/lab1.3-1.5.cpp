#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;

template <class T>
class Element {
private:
	Element* next;
	Element* prev;

	T field;
public:
	virtual Element* getNext() {
		return next;
	}
	virtual void setNext(Element* value) {
		next = value;
	}

	virtual Element* getPrevious() {
		return prev;
	}
	virtual void setPrevious(Element* value) {
		prev = value;
	}

	virtual T getValue() {
		return field;
	}
	virtual void setValue(T value) {
		field = value;
	}

	Element() {
		next = prev = NULL;
	}
	Element(T value) {
		next = prev = NULL;
		field = value;
	}

	virtual~Element() {
		if (next) delete next;
		next = NULL;
		prev = NULL;
	}

	bool operator> (T value) {
		if (field > value)
			return true;
		else
			return false;
	}

	template <class T> friend ostream& operator <<(ostream& ustream, Element <T>& obj);
};
template <class T>
class LinkedListParent {
protected:
	Element <T>* head;
	Element <T>* tail;
	int num;
public:
	virtual int Number() {
		return num;
	}

	virtual Element <T>* getBegin() {
		return head;
	}

	virtual Element <T>* getEnd() {
		return tail;
	}

	LinkedListParent() {
		head = NULL;
		num = 0;
	}

	virtual Element <T>* push(T value) = 0;

	virtual Element <T>* pop() = 0;

	virtual~LinkedListParent() {
		if (head) delete head;
		head = NULL;
		tail = NULL;
	}

	virtual Element <T>* operator[](int i) {
		if (i <0 || i> num) return NULL;
		int k = 0;

		Element <T>* cur = head;
		for (k = 0; k < i; k++) {
			cur = cur->getNext();
		}
		return cur;
	}

	template <class T>
	friend ostream& operator <<(ostream& ustream, LinkedListParent <T>& obj);
	template <class T>
	friend istream& operator>> (istream& ustream, LinkedListParent <T>& obj);
};

template <class T>
ostream& operator <<(ostream& ustream, Element <T>& obj) {
	ustream << obj.field;
	return ustream;
}


template <class T>
ostream& operator <<(ostream& ustream, LinkedListParent <T>& obj) {
	if (typeid(ustream).name() == typeid(ofstream).name()) {
		ustream << obj.num << endl;
		for (Element <T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue();
		return ustream;
	}

	ustream << "\nLen" << obj.num << endl;
	int i = 0;
	for (Element <T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "]= " << current->getValue() << endl;

	return ustream;
}

template <class T>
istream& operator>> (istream& ustream, LinkedListParent <T>& obj) {
	int len;
	ustream >> len;

	if (obj.head) delete obj.head;
	obj.head = NULL;
	obj.tail = NULL;
	obj.num = 0;

	double v = 0;
	for (int i = 0; i < len; i++) {
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

template <typename ValueType>
class ListIterator : public std::iterator <std::input_iterator_tag, ValueType> {
private: Element <ValueType>* ptr;
public: ListIterator() {
	ptr = NULL;
}
	  ListIterator(Element <ValueType>* p) {
		  ptr = p;
	  }
	  ListIterator(const ListIterator& it) {
		  ptr = it.ptr;
	  }

	  ListIterator& operator = (const ListIterator& it) {
		  ptr = it.ptr;
		  return *this;
	  }
	  ListIterator& operator = (Element <ValueType>* p) {
		  ptr = p;
		  return *this;
	  }

	  bool operator != (ListIterator
		  const& other) const {
		  return ptr != other.ptr;
	  }
	  bool operator == (ListIterator
		  const& other) const {
		  return ptr == other.ptr;
	  }

	  Element <ValueType>& operator * () {
		  return *ptr;
	  }

	  ListIterator& operator++() {
		  if (ptr != NULL || ptr->getNext() != NULL)
			  ptr = ptr->getNext();
		  return *this;
	  }

	  ListIterator& operator++(int v) {
		  if (ptr != NULL || ptr->getNext() != NULL)
			  ptr = ptr->getNext();
		  return *this;
	  }

	  ListIterator& operator--() {
		  ptr = ptr->getPrevious();
		  return *this;
	  }

	  ListIterator& operator--(int) {
		  ListIterator before = *this;
		  --(*this);
		  return before;
	  }
};

template <class T>
class IteratedLinkedList : public LinkedListParent <T> {
public: IteratedLinkedList() : LinkedListParent <T>() {}
	  virtual~IteratedLinkedList() {}

	  ListIterator <T> iterator;

	  ListIterator <T> begin() {
		  ListIterator <T> it = LinkedListParent <T> ::head;
		  return it;
	  }
	  ListIterator <T> end() {
		  ListIterator <T> it = LinkedListParent <T> ::tail;
		  return it;
	  }
};

template <class T>
class Stack : public IteratedLinkedList <T> {
public: Stack() : IteratedLinkedList <T>() {}
	  virtual~Stack() {}

	  virtual Element <T>* push(T value) {
		  if (LinkedListParent <T> ::num != 0) {
			  Element <T>* newElem = new Element <T>(value);
			  LinkedListParent <T> ::tail->setNext(newElem);
			  newElem->setPrevious(LinkedListParent <T> ::tail);

			  LinkedListParent <T> ::tail = LinkedListParent <T> ::tail->getNext();
		  }
		  else {
			  LinkedListParent <T> ::tail = new Element <T>(value);
			  LinkedListParent <T> ::head = LinkedListParent <T> ::tail;
		  }
		  LinkedListParent <T> ::num++;
		  return LinkedListParent <T> ::tail;
	  }

	  virtual Element <T>* pop() {
		  if (IteratedLinkedList <T> ::head == NULL) {
			  return NULL;
		  }

		  Element <T>* res = IteratedLinkedList <T> ::head;
		  if (IteratedLinkedList <T> ::head == IteratedLinkedList <T> ::tail) {
			  delete IteratedLinkedList <T> ::head;
			  IteratedLinkedList <T> ::head = IteratedLinkedList <T> ::tail = NULL;
		  }
		  else {
			  LinkedListParent <T> ::tail = LinkedListParent <T> ::tail->getPrevious();
			  IteratedLinkedList <T> ::tail->getNext()->setPrevious(NULL);
			  delete IteratedLinkedList <T> ::tail->getNext();
			  IteratedLinkedList <T> ::tail->setNext(NULL);
		  }
		  IteratedLinkedList <T> ::num--;
		  return res;
	  }

	  template <class T>
	  void filter(IteratedLinkedList <T>* source, IteratedLinkedList <T>* destination, bool(*ptr_f)(T)) {
		  ListIterator <T> p = source->begin();

		  while (p != source->end()) {
			  if (ptr_f((*p).getValue())) {
				  destination->push((*p).getValue());
			  }
			  p++;
		  }
		  ListIterator <T> p1 = source->end();
		  if (ptr_f((*p1).getValue())) {
			  destination->push((*p).getValue());
		  }
	  }
};

template <class T>
class StackChild : public Stack <T> {
public:

	StackChild() : Stack <T>() {}
	virtual~StackChild() {}

	virtual Element <T>* push(T value) {
		Element <T>* result = NULL;
		ListIterator <T> p = Stack <T> ::begin();
		int k = 0;
		int Num = Stack <T> ::Number();

		while (k != Num) {
			Element <T>& element = *p;
			if ((element.getValue() > value) && (result == NULL)) {
				result = Stack <T> ::push(value);
			}
			Stack <T> ::push(element.getValue());
			p++;
			k++;
			Stack <T> ::pop();
		}

		if (result == NULL) {
			result = Stack <T> ::push(value);
		}

		return result;
	}
};

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

ostream& operator <<(ostream& ustream,
	const program& obj) {
	ustream << "Price " << obj.Price << " Version " << obj.Version <<
		" Name " << obj.Name << " ";
	ustream << endl;

	return ustream;
}

bool predicate(char letter) {
	if (islower(letter)) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	Stack <char> s1;
	Stack <char> s2;
	s1.push('U');
	s1.push('w');
	s1.push('u');
	s1.push('O');
	s1.push('w');
	s1.push('O');
	cout << endl << s1;
	s1.pop();
	cout << endl << s1;
	IteratedLinkedList <char>* ptr1 = &s1;
	IteratedLinkedList <char>* ptr2 = &s2;
	s1.filter(ptr1, ptr2, predicate);
	cout << endl << 2;
	StackChild <program> s3;

	program firstName(5000, 13, "Valorant");
	program secondName(-0, 145, "Minecraft");
	program thirdName(-1234, 123, "World of Warcraft");

	s3.push(firstName);
	s3.push(secondName);
	s3.push(thirdName);
	cout << s3;

	return 0;
}