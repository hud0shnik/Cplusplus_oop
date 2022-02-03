#include "StdAfx.h"
#include <iostream>
#include <fstream>



using namespace std;



template <class T>
class Element
{
private:
	Element* next;
	Element* prev;
	T field;
public:
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

 	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	Element() { next = prev = NULL; }
	Element(T value) { next = prev = NULL; field = value; }

	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected: 
	Element<T>* head;
	Element<T>* tail; 
	int num;
public:
	virtual int Number() { return num; }

	virtual Element<T>* getBegin() { return head; }

	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent()
	{ 
		cout << "\nParent constructor";
		head = NULL;
		num = 0;
	}
	 
	virtual Element<T>* push(T value) = 0;
	 
	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent()
	{ 
		cout << "\nParent destructor";
	} 

	virtual Element<T>* operator[](int i)
	{ 
		if (i<0 || i>num) return NULL;
		int k = 0;
		 
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{ 
	int len;
	ustream >> len; 
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}
 
template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:

public: 
	ListIterator() { ptr = NULL; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }
	 
	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }
	 
	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const { return ptr == other.ptr; }
	 
	Element<ValueType>& operator*()
	{
		return *ptr;
	} 
	ListIterator& operator++() {
		if (ptr != NULL || ptr->getNext() != NULL) {
			ptr = ptr->getNext();
		}
		return *this;
	}
	ListIterator& operator++(int v) {
		if (ptr != NULL || ptr->getNext() != NULL) {
			ptr = ptr->getNext();
		}
		return *this;
	}
	//
	ListIterator& operator--() {
		if (ptr != NULL || ptr->getPrevious() != NULL) {
			ptr = ptr->getPrevious();
		}
		return *this;
	}
	ListIterator& operator--(int v) {
		if (ptr != NULL || ptr->getPrevious() != NULL) {
			ptr = ptr->getPrevious();
		}
		return *this;
	}
private: 
	Element<ValueType>* ptr;
};
 
template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor"; }

	ListIterator<T> iterator;

	ListIterator<T> begin() { ListIterator<T> it = LinkedListParent<T>::head; return it; }
	ListIterator<T> end() { ListIterator<T> it = LinkedListParent<T>::tail; return it; }
};

template <class T>
class Queue : public IteratedLinkedList<T>
{
public:
	Queue() : IteratedLinkedList<T>() { cout << "\nQueue constructor"; }
	virtual ~Queue() { cout << "\nQueue destructor"; }
	LinkedListParent<T>::num;
	virtual Element<T>* push(T value)
	{
		if (num != 0) {
			Element<T>* newElem = new Element<T>(value);
			tail->setNext(newElem);
			newElem->setPrevious(tail);

			tail = tail->getNext();
		}
		else {
			tail = new Element<T>(value);
			head = tail;
		}
		num++;
		return tail;
	}

	virtual Element<T>* pop()
	{
		return NULL;
	}

	Queue<T> filter(bool (*ptr_func) (T))
	{

		Queue<T> res;
		//
		iterator = begin();
		while (iterator != end())
		{
			if (ptr_func((*iterator).getValue()))
				res.push((*iterator).get_Value());
			iterator++;
		}
		// cout << *iterator << " ";
		if (num > 0 && ptr_func((*iterator).getValue()))
			res.push((*iterator).getValue());
		return res;

	}
};

bool condition(int value)
{
	return (value % 2 != 0);
}


int main()
{
	Queue<int> S;
	S.push(1);
	S.push(2);
	S.push(3);
	cout << S;
	cout << "\n";
	//Element* e1 = S.pop();
	//cout << "\nElement = " << e1->getValue();
	cout << S;
	cout << "\nIndex in the Stack class: " << S[1]->getValue();

	cout << S;
	cout << "\nIterators:\n";
	S.iterator = S.begin();
	while (S.iterator != S.end())
	{
		cout << *S.iterator << " ";
		S.iterator++;
	}
	cout << *S.iterator << " ";

	Queue<int> S1 = S.filter(coundition);
	cout < "\nFilter:" << S1;

	char c; cin >> c;
	return 0;
}
