#include <iostream>
#include <fstream>
#include <complex>

using namespace std;
// 4 вариант - Стек

template < class T >
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

    bool operator > (T value) {
        if (field > value)
            return true;
        else
            return false;
    }

    template < class T > friend ostream& operator << (ostream& ustream, Element < T >& obj);
};

template < class T >
ostream& operator << (ostream& ustream, Element < T >& obj) {
    ustream << obj.field;
    return ustream;
}

template < class T >
class LinkedListParent {
protected:
    Element < T >* head;
    Element < T >* tail;
    int num;
public:
    virtual int Number() {
        return num;
    }

    virtual Element < T >* getBegin() {
        return head;
    }

    virtual Element < T >* getEnd() {
        return tail;
    }

    LinkedListParent() {
        head = NULL;
        num = 0;
    }

    virtual Element < T >* push(T value) = 0;

    virtual Element < T >* pop() = 0;

    virtual~LinkedListParent() {
        if (head) delete head;
        head = NULL;
        tail = NULL;
    }

    virtual Element < T >* operator[](int i) {
        if (i < 0 || i > num) return NULL;
        int k = 0;

        Element < T >* cur = head;
        for (k = 0; k < i; k++) {
            cur = cur->getNext();
        }
        return cur;
    }

    template < class T >
    friend ostream& operator << (ostream& ustream, LinkedListParent < T >& obj);
    template < class T >
    friend istream& operator >> (istream& ustream, LinkedListParent < T >& obj);
};

template < class T >
ostream& operator << (ostream& ustream, LinkedListParent < T >& obj) {
    if (typeid(ustream).name() == typeid(ofstream).name()) {
        ustream << obj.num << "\n";
        for (Element < T >* current = obj.getBegin(); current != NULL; current = current->getNext())
            ustream << current->getValue() << " ";
        return ustream;
    }

    ustream << "\nLength: " << obj.num << "\n";
    int i = 0;
    for (Element < T >* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
        ustream << "arr[" << i << "] = " << current->getValue() << "\n";

    return ustream;
}

template < class T >
istream& operator >> (istream& ustream, LinkedListParent < T >& obj) {
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

template < typename ValueType >
class ListIterator : public std::iterator < std::input_iterator_tag, ValueType > {
private: Element < ValueType >* ptr;
public: ListIterator() {
    ptr = NULL;
}
      ListIterator(Element < ValueType >* p) {
          ptr = p;
      }
      ListIterator(const ListIterator& it) {
          ptr = it.ptr;
      }

      ListIterator& operator = (const ListIterator& it) {
          ptr = it.ptr;
          return *this;
      }
      ListIterator& operator = (Element < ValueType >* p) {
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

      Element < ValueType >& operator * () {
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

template < class T >
class IteratedLinkedList : public LinkedListParent < T > {
public: IteratedLinkedList() : LinkedListParent < T >() {}
      virtual~IteratedLinkedList() {}

      ListIterator < T > iterator;

      ListIterator < T > begin() {
          ListIterator < T > it = LinkedListParent < T > ::head;
          return it;
      }
      ListIterator < T > end() {
          ListIterator < T > it = LinkedListParent < T > ::tail;
          return it;
      }
};

template < class T >
class Stack : public IteratedLinkedList < T > {
public: Stack() : IteratedLinkedList < T >() {}
      virtual~Stack() {}

      virtual Element < T >* push(T value) {
          if (LinkedListParent < T > ::num != 0) {
              Element < T >* newElem = new Element < T >(value);
              LinkedListParent < T > ::tail->setNext(newElem);
              newElem->setPrevious(LinkedListParent < T > ::tail);

              LinkedListParent < T > ::tail = LinkedListParent < T > ::tail->getNext();
          }
          else {
              LinkedListParent < T > ::tail = new Element < T >(value);
              LinkedListParent < T > ::head = LinkedListParent < T > ::tail;
          }
          LinkedListParent < T > ::num++;
          return LinkedListParent < T > ::tail;
      }

      virtual Element < T >* pop() {
          if (IteratedLinkedList < T > ::head == NULL) {
              return NULL;
          }

          Element < T >* res = IteratedLinkedList < T > ::head;
          if (IteratedLinkedList < T > ::head == IteratedLinkedList < T > ::tail) {
              delete IteratedLinkedList < T > ::head;
              IteratedLinkedList < T > ::head = IteratedLinkedList < T > ::tail = NULL;
          }
          else {
              LinkedListParent < T > ::tail = LinkedListParent < T > ::tail->getPrevious();
              IteratedLinkedList < T > ::tail->getNext()->setPrevious(NULL);
              delete IteratedLinkedList < T > ::tail->getNext();
              IteratedLinkedList < T > ::tail->setNext(NULL);
          }
          IteratedLinkedList < T > ::num--;
          return res;
      }

      template < class T >
      void filter(IteratedLinkedList < T >* source, IteratedLinkedList < T >* destination, bool(*ptr_f)(T)) {
          ListIterator < T > p = source->begin();

          while (p != source->end()) {
              if (ptr_f((*p).getValue())) {
                  destination->push((*p).getValue());
              }
              p++;
          }
          ListIterator < T > p1 = source->end();
          if (ptr_f((*p1).getValue())) {
              destination->push((*p).getValue());
          }
      }
};

template < class T >
class StackChild : public Stack < T > {
public:

    StackChild() : Stack < T >() {}
    virtual~StackChild() {}

    virtual Element < T >* push(T value) {
        Element < T >* result = NULL;
        ListIterator < T > p = Stack < T > ::begin();
        int k = 0;
        int Num = Stack < T > ::Number();

        while (k != Num) {
            Element < T >& element = *p;
            if ((element.getValue() > value) && (result == NULL)) {
                result = Stack < T > ::push(value);
            }
            Stack < T > ::push(element.getValue());
            p++;
            k++;
            Stack < T > ::pop();
        }

        if (result == NULL) {
            cout << "work1" << endl;
            result = Stack < T > ::push(value);
        }

        return result;
    }
};

class sportsman {
private:
    int Medals;
    int Age;
    string Name;
    string LastName;
    string Citizenship;
    string Sport;

public:
    sportsman() {
        Medals = 0;
        Age = 0;
        Name = "";
    }

    sportsman(int medals, int age, string name, string lastname, string citizenship, string sport) {
        Medals = medals;
        Age = age;
        Name = name;
        LastName = lastname;
        Citizenship = citizenship;
        Sport = sport;
    }
    sportsman(int medals, int age, string name) {
        Medals = medals;
        Age = age;
        Name = name;
    }

    bool operator > (sportsman& L) {
        bool res = false;
        if (Medals > L.Medals)
            res = true;
        else if (Medals == L.Medals)
            if (Age > L.Age)
                res = true;
            else if (Age == L.Age)
                if (Name > L.Name)
                    res = true;
                else if (Name == L.Name)
                    if (LastName > L.LastName)
                        res = true;
                    else if (LastName == L.LastName)
                        cout << "error";
        return res;
    }

    bool operator == (sportsman& L) {
        if ((Medals == L.Medals) & (Age == L.Age) & (Name == L.Name) & (LastName == L.LastName))
            return true;
        else
            return false;
    }

    friend ostream& operator << (ostream& ustream,
        const sportsman& obj);
};

ostream& operator << (ostream& ustream,
    const sportsman& obj) {
    ustream << "Medals: " << obj.Medals << " Age: " << obj.Age <<
        " Name: " << obj.Name;
    ustream << endl;

    return ustream;
}

template < class T >
bool P(T element) {
    if (real(element) < 0) {
        return true;
    }
    return false;
}

int main() {
    Stack < complex < int >> stack1;
    Stack < complex < int >> stack2;
    StackChild < sportsman > stack3;

    stack1.push(-3);
    stack1.push(0);
    stack1.push(1);
    stack1.push(2);
    stack1.push(8);
    stack1.push(13);
    stack1.push(55);
    stack1.push(56);

    cout << stack1;

    stack1.pop();

    cout << stack1;

    IteratedLinkedList < complex < int >>* ptr1 = &stack1;
    IteratedLinkedList < complex < int >>* ptr2 = &stack2;

    stack1.filter(ptr1, ptr2, P);
    cout << stack2;

    sportsman first(99, 28, "Johny");
    sportsman second(13, 28, "Arnold");
    sportsman third(418, 13, "Sanya Teapod");

    stack3.push(first);
    stack3.push(second);
    stack3.push(third);

    cout << stack3;

    return 0;
}