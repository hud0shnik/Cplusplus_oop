#include <iostream>
#include <fstream>
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
ostream& operator <<(ostream& ustream, Element <T>& obj) {
	ustream << obj.field;
	return ustream;
}

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
ostream& operator <<(ostream& ustream, LinkedListParent <T>& obj) {
	if (typeid(ustream).name() == typeid(ofstream).name()) {
		ustream << obj.num << "\n";
		for (Element <T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element <T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

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
class Qeue : public IteratedLinkedList <T> {
public: Qeue() : IteratedLinkedList <T>() {}
	  virtual~Qeue() {}

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
class QeueChild : public Qeue <T> {
public:

	QeueChild() : Qeue <T>() {}
	virtual~QeueChild() {}

	virtual Element <T>* push(T value) {
		Element <T>* result = NULL;
		ListIterator <T> p = Qeue <T> ::begin();
		int k = 0;
		int Num = Qeue <T> ::Number();

		while (k != Num) {
			Element <T>& element = *p;
			if ((element.getValue() > value) && (result == NULL)) {
				result = Qeue <T> ::push(value);
			}
			Qeue <T> ::push(element.getValue());
			p++;
			k++;
		}

		if (result == NULL) {
			result = Qeue <T> ::push(value);
		}

		return result;
	}
};

class smartPhone {
private:
	int Price;
	int Camera;
	string Name;
	string Size;
	string Battery;

public:
	smartPhone() {
		Price = 0;
		Camera = 0;
		Name = "";
		Size = "";
		Battery = "";
	}

	smartPhone(int price, int camera, string name, string size, string Battery, string webSite) {
		Price = price;
		Camera = camera;
		Name = name;
		Size = size;
		Battery = Battery;
	}

	smartPhone(int price, int camera, string name) {
		Price = price;
		Camera = camera;
		Name = name;
	}

	bool operator > (smartPhone& L) {
		bool res = false;
		if (Price > L.Price)
			res = true;
		else if (Price == L.Price)
			if (Camera > L.Camera)
				res = true;
			else if (Camera == L.Camera)
				if (Name > L.Name)
					res = true;
				else if (Name == L.Name)
					if (Size > L.Size)
						res = true;
					else if (Size == L.Size)
						cout << "error";
		return res;
	}

	bool operator == (smartPhone& L) {
		if ((Price == L.Price) & (Camera == L.Camera) & (Name == L.Name) & (Size == L.Size))
			return true;
		else
			return false;
	}

	friend ostream& operator << (ostream& result,
		const smartPhone& obj);
};

ostream& operator << (ostream& result, const smartPhone& obj) {
	if (obj.Battery == "" & obj.Size == "") {
		result << "Price: " << obj.Price << " Camera: " << obj.Camera <<
			" Name: " << obj.Name;
		result << endl;
	}
	else {
		result << "Price: " << obj.Price << " Camera: " << obj.Camera <<
			" Name: " << obj.Name << " Size: " << obj.Size << " Battery: " << obj.Battery;
		result << endl;
	}

	return result;
}

bool P(int element) {
	for (int i = 2; i < element; i++) {
		if (element % i == 0) {
			return false;
		}
	}
	return true;
}


int main() {
	return 0;
}