#include <list>
#include <iostream>
#include <fstream>

using namespace std;
template < class T >
void push(list < T >& lst, T element, bool isBigger = true) {
    auto p = lst.begin();
    while (p != lst.end()) {
        if (isBigger ? *p > element : *p < element)
            break;
        p++;
    }
    lst.insert(p, element);
}

class aviaCompany {
private:
    int Reliability;
    int Lines;
    string Name;
    string Code;
    string Country;
    string WebSite;

public:
    aviaCompany() {
        Reliability = 0;
        Lines = 0;
        Name = "";
        Code = "";
        Country = "";
        WebSite = "";
    }

    aviaCompany(int reliability, int lines, string name, string code, string country, string webSite) {
        Reliability = reliability;
        Lines = lines;
        Name = name;
        Code = code;
        Country = country;
        WebSite = webSite;
    }

    aviaCompany(int reliability, int lines, string name) {
        Reliability = reliability;
        Lines = lines;
        Name = name;
    }

    bool operator > (aviaCompany& L) {
        bool res = false;
        if (Reliability > L.Reliability)
            res = true;
        else if (Reliability == L.Reliability)
            if (Lines > L.Lines)
                res = true;
            else if (Lines == L.Lines)
                if (Name > L.Name)
                    res = true;
                else if (Name == L.Name)
                    if (Code > L.Code)
                        res = true;
                    else if (Code == L.Code)
                        cout << "error";
        return res;
    }

    bool operator == (aviaCompany& L) {
        if ((Reliability == L.Reliability) & (Lines == L.Lines) & (Name == L.Name) & (Code == L.Code))
            return true;
        else
            return false;
    }

    friend ostream& operator << (ostream& result,
        const aviaCompany& obj);
};

template < class T >
T pop(list < T >& lst, size_t pos) {
    if (pos >= lst.size())
        return T{};

    auto p = lst.begin();
    size_t i = 0;
    T res;
    while (p != lst.end()) {
        auto& lastval = *p;
        p++;
        if (i == pos)
            res = lastval;

        if (i >= pos) {
            if (p != lst.end())
                lastval = *p;
        }
        i++;
    }
    lst.pop_back();
    return res;
}

template < class T >
void print(list < T >& lst) {
    auto p = lst.begin();
    while (p != lst.end()) {
        cout << *p << " ";
        p++;
    }
    cout << endl;
}

template < class T >
list < T > filter(list < T >& lst, bool(*fn)(T cur, T a), T A) {
    list < T > newlist;
    auto p = lst.begin();
    while (p != lst.end()) {
        if (fn(*p, A))
            push(newlist, *p);
        p++;
    }
    return newlist;
}

bool filter(int cur) {
    int f = 0, f1 = 1, f2 = 1;
    while (f < cur) {
        f = f2 + f1;
        f2 = f1;
        f1 = f;
    }
    return f == cur;
}

ostream& operator << (ostream& result,
    const aviaCompany& obj) {
    if (obj.Country == "" & obj.Code == "" & obj.WebSite == "") {
        result << "Reliability: " << obj.Reliability << " Lines: " << obj.Lines <<
            " Name: " << obj.Name;
        result << endl;
    }
    else {
        result << "Reliability: " << obj.Reliability << " Lines: " << obj.Lines <<
            " Name: " << obj.Name << " Code: " << obj.Code << " Sitizenship: " << obj.Country << " WebSite: " << obj.WebSite;
        result << endl;
    }

    return result;
}

template < class T >
class Element {
protected:
    Element* next;
    Element* prev;
    T info;
public:
    T& GetInfo() {
        return info;
    }
    Element* GetNext() {
        return next;
    }
    Element* GetPrev() {
        return prev;
    }
    void SetInfo(T NewInfo) {
        info = NewInfo;
    }
    void SetNext(Element* NewNext) {
        next = NewNext;
    }
    void SetPrev(Element* NewPrev) {
        prev = NewPrev;
    }
    Element(T data) {
        next = prev = NULL;
        info = data;
    }
    Element(Element* Next, Element* Prev, T data) {
        next = Next;
        prev = Prev;
        info = data;
    }
    Element(const Element& el) {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }
    template < class T1 >
    friend ostream& operator << (ostream& s, Element < T1 >& el);
};

template < class T1 >
ostream& operator << (ostream& s, Element < T1 >& el) {
    s << el.info;
    return s;
}

template < class T >
class LinkedList {
protected:
    Element < T >* head;
    Element < T >* tail;
    int count;
public:
    int GetCount() {
        return count;
    }
    void SetCount(int NewCount) {
        count = NewCount;
    }
    Element < T >* GetHead() {
        return head;
    }
    void SetHead(Element < T >* NewHead) {
        head = NewHead;
    }
    Element < T >* GetTail() {
        return tail;
    }
    void SetTail(Element < T >* NewTail) {
        tail = NewTail;
    }
    LinkedList() {
        head = tail = NULL;
        count = 0;
    }
    virtual Element < T >* pop() = 0;
    virtual Element < T >* push(T value) = 0;
    virtual Element < T >* operator[](int i) {
        if (i < 0 || i > count) return NULL;
        int k = 0;

        Element < T >* cur = head;
        for (k = 0; k < i; k++) {
            cur = cur->GetNext();
        }
        return cur;
    }
    virtual Element < T >* GetElement(int i) {
        if (i < 0 || i > count) return NULL;
        int k = 0;

        Element < T >* cur = head;
        for (k = 0; k < i; k++) {
            cur = cur->GetNext();
        }
        return cur;
    }
    virtual bool isEmpty() {
        return (LinkedList < T > ::count == 0);
    }
    template < class T > friend ostream& operator << (ostream& ustream, LinkedList < T >& obj);
    template < class T > friend istream& operator >> (istream& ustream, LinkedList < T >& obj);
    virtual Element < T >* Delete(int index) {
        if (LinkedList < T > ::head == NULL)
            return NULL;
        Element < T >* res = LinkedList < T > ::head;
        if (LinkedList < T > ::head == LinkedList < T > ::tail)
            LinkedList < T > ::head = LinkedList < T > ::tail = NULL;
        else {
            Element < T >* current = LinkedList < T > ::head;
            for (int i = 0; current != NULL && i < index; current = current->GetNext(), i++);

            Element < T >* Previous = current->GetPrev();
            Element < T >* Next = current->GetNext();
            Previous->SetNext(Next);
            Next->SetPrev(Previous);

            delete current;
        }
        LinkedList < T > ::count--;
        return res;
    }
    virtual~LinkedList() {
        while (count != 0) {
            if (count == 2) {
                if (LinkedList < T > ::head) {
                    delete LinkedList < T > ::head;
                    LinkedList < T > ::head = 0;
                }
                if (LinkedList < T > ::tail) {
                    delete LinkedList < T > ::tail;
                    LinkedList < T > ::tail = 0;
                }
                count = 0;
                break;
            }
            else
                Delete(1);
        }
    }
};

template < class T >
ostream& operator << (ostream& ustream, LinkedList < T >& obj) {
    if (typeid(ustream).name() == typeid(ofstream).name()) {
        ustream << obj.count << "\n";
        for (Element < T >* current = obj.GetHead(); current != NULL; current = current->GetNext())
            ustream << current->GetInfo() << " ";
        return ustream;
    }

    ustream << "\nLength: " << obj.count << "\n";
    int i = 0;
    for (Element < T >* current = obj.GetHead(); current != NULL; current = current->GetNext(), i++)
        ustream << "arr[" << i << "] = " << current->GetInfo() << "\n";

    return ustream;
}

template < class T >
istream& operator >> (istream& ustream, LinkedList < T >& obj) {
    int len;
    ustream >> len;
    T v = 0;
    for (int i = 0; i < len; i++) {
        ustream >> v;
        obj.push(v);
    }
    return ustream;
}

template < typename ValueType >
class ListIterator : public std::iterator < std::input_iterator_tag, ValueType > {
public: ListIterator() {
    ptr = NULL;
}
      ListIterator(Element < ValueType >* p) {
          ptr = p;
      }
      ListIterator(const ListIterator& it) {
          ptr = it.ptr;
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
          if (ptr != NULL && ptr->GetNext() != NULL)
              ptr = ptr->GetNext();
          return *this;
      }
      ListIterator& operator++(int v) {
          if (ptr != NULL && ptr->GetNext() != NULL) ptr = ptr->GetNext();
          return *this;
      }
      ListIterator& operator--() {
          if (ptr != NULL && ptr->GetPrev() != NULL)
              ptr = ptr->GetPrev();
          return *this;
      }
      ListIterator& operator--(int v) {
          if (ptr != NULL && ptr->GetPrev() != NULL) ptr = ptr->GetPrev();
          return *this;
      }
      ListIterator& operator = (const ListIterator& it) {
          ptr = it.ptr;
          return *this;
      }
      bool operator == (const ListIterator& it) {
          return ptr == it.ptr;
      }
      bool operator != (const ListIterator& it) {
          return ptr != it.ptr;
      }
      ListIterator& operator = (Element < ValueType >* p) {
          ptr = p;
          return *this;
      }
private: Element < ValueType >* ptr;
};

template < class T >
class IteratedLinkedList : public LinkedList < T > {
public: IteratedLinkedList() : LinkedList < T >() {}
      virtual~IteratedLinkedList() {}
      ListIterator < T > begin() {
          ListIterator < T > it = LinkedList < T > ::head;
          return it;
      }
      ListIterator < T > end() {
          ListIterator < T > it = LinkedList < T > ::tail;
          return it;
      }
      template < class T > friend ostream& operator << (ostream& ustream, IteratedLinkedList < T >& obj);
};

template < class T >
ostream& operator << (ostream& ustream, IteratedLinkedList < T >& obj) {
    if (typeid(ustream).name() == typeid(ofstream).name()) {
        ustream << obj.GetCount() << "\n";
        ListIterator < T > p = obj.begin();
        while (p != obj.end()) {
            ustream << *p << " ";
            p++;
        }
        if (p == obj.end())
            ustream << *p << " ";

        return ustream;
    }

    ustream << "\nLength: " << obj.GetCount() << "\n";
    int i = 0;
    ListIterator < T > p = obj.begin();
    while (p != obj.end()) {
        ustream << "arr[" << i << "] = " << *p << endl;
        p++;
        i++;
    }
    if (p == obj.end())
        ustream << "arr[" << i << "] = " << *p << endl;
    return ustream;
}

template < class T >
class Stack : public IteratedLinkedList < T > {
public: Stack < T >() : IteratedLinkedList < T >() {}
      Stack < T >(T* arr, int len) : IteratedLinkedList < T >(arr, len) {}
      virtual Element < T >* push(T value)
      {
          if (LinkedList < T > ::head == NULL)
          {
              LinkedList < T > ::head = new Element < T >(value);
              LinkedList < T > ::tail = LinkedList < T > ::head;
          }
          else {
              LinkedList < T > ::tail->SetNext(new Element < T >(value));
              LinkedList < T > ::tail->GetNext()->SetPrev(LinkedList < T > ::tail);
              LinkedList < T > ::tail = LinkedList < T > ::tail->GetNext();
          }
          LinkedList < T > ::count++;
          return LinkedList < T > ::tail;
      }
      virtual Element < T >* pop()
      {
          if (LinkedList < T > ::head == NULL)
              return NULL;

          Element < T >* res = LinkedList < T > ::tail;
          if (LinkedList < T > ::head == LinkedList < T > ::tail)
              LinkedList < T > ::head = LinkedList < T > ::tail = NULL;
          else {
              Element < T >* NewTail = LinkedList < T > ::tail->GetPrev();
              NewTail->SetNext(NULL);
              LinkedList < T > ::tail = NewTail;
          }
          LinkedList < T > ::count--;
          return res;
      }
      virtual Element < T >* Insert(T value, int index) {
          if (LinkedList < T > ::head == NULL)
          {
              LinkedList < T > ::head = new Element < T >(value);
              LinkedList < T > ::tail = LinkedList < T > ::head;
              LinkedList < T > ::count++;
              return LinkedList < T > ::tail;
          }
          else {
              Element < T >* current = LinkedList < T > ::head;
              for (int i = 0; current != NULL && i < index; current = current->GetNext(), i++);

              Element < T >* NewElement = new Element < T >(current, current->GetPrev(), value);
              current->GetPrev()->SetNext(NewElement);
              current->SetPrev(NewElement);
              LinkedList < T > ::count++;
              return NewElement;
          }
      }
      virtual Stack < T >* Filter(T value, bool(*Compare)(T Cur, T Val)) {
          Stack < T >* Filtered = new Stack < T >;
          for (int i = 0; i < LinkedList < T > ::GetCount(); i++) {
              Element < T >* Current = LinkedList < T > ::GetElement(i);
              if (Compare(Current->GetInfo(), value))
                  Filtered->push(Current->GetInfo());
          }
          return Filtered;
      }
      virtual Stack < T >* FilterRecursevly(T value, int start, int end, bool(*Compare)(T Cur, T Val), Stack < T >* Filtered) {
          Element < T >* Left = LinkedList < T > ::GetElement(start);
          Element < T >* Right = LinkedList < T > ::GetElement(end);

          if (start == end + -1) {
              if (Compare(Left->GetInfo(), value))
                  Filtered->push(Left->GetInfo());
              if (Compare(Right->GetInfo(), value))
                  Filtered->push(Right->GetInfo());

              return Filtered;
          }
          if (end - start == 2) {
              int middle = (start + end) / 2;
              Element < T >* Middle = LinkedList < T > ::GetElement(middle);

              if (Compare(Left->GetInfo(), value))
                  Filtered->push(Left->GetInfo());
              if (Compare(Right->GetInfo(), value))
                  Filtered->push(Right->GetInfo());
              if (Compare(Middle->GetInfo(), value))
                  Filtered->push(Middle->GetInfo());

              return Filtered;
          }

          if (Compare(Left->GetInfo(), value))
              Filtered->push(Left->GetInfo());
          if (Compare(Right->GetInfo(), value))
              Filtered->push(Right->GetInfo());

          return FilterRecursevly(value, start + 1, end - 1, Compare, Filtered);
      }
      virtual~Stack() {}
};

template < class T >
class SortedStack : public Stack < T > {
public: virtual Element < T >* push(T value) {
    if (this->GetCount() == 0)
    {

        LinkedList < T > ::head = new Element < T >(value);
        LinkedList < T > ::tail = LinkedList < T > ::head;
        LinkedList < T > ::count++;
        return LinkedList < T > ::tail;
    }
    else if (this->GetCount() == 1) {

        if (LinkedList < T > ::head->GetInfo() < value) {
            Element < T >* OldHead = LinkedList < T > ::head;
            Element < T >* NewHead = new Element < T >(value);
            OldHead->SetPrev(NewHead);
            NewHead->SetNext(OldHead);
            LinkedList < T > ::head = NewHead;
            LinkedList < T > ::count++;
            return LinkedList < T > ::head;
        }
        else {
            LinkedList < T > ::tail->SetNext(new Element < T >(value));
            LinkedList < T > ::tail->GetNext()->SetPrev(LinkedList < T > ::tail);
            LinkedList < T > ::tail = LinkedList < T > ::tail->GetNext();
            LinkedList < T > ::count++;
            return LinkedList < T > ::tail;
        }
    }
    else {
        if (value < LinkedList < T > ::tail->GetInfo()) {
            LinkedList < T > ::tail->SetNext(new Element < T >(value));
            LinkedList < T > ::tail->GetNext()->SetPrev(LinkedList < T > ::tail);
            LinkedList < T > ::tail = LinkedList < T > ::tail->GetNext();
            LinkedList < T > ::count++;
            return LinkedList < T > ::tail;
        }
        else if (value > LinkedList < T > ::head->GetInfo()) {
            Element < T >* OldHead = LinkedList < T > ::head;
            Element < T >* NewHead = new Element < T >(value);
            OldHead->SetPrev(NewHead);
            NewHead->SetNext(OldHead);
            LinkedList < T > ::head = NewHead;
            LinkedList < T > ::count++;
            return LinkedList < T > ::head;
        }
        for (Element < T >* current = LinkedList < T > ::head; current != NULL; current = current->GetNext()) {
            if (current->GetInfo() < value) {
                Element < T >* NewElement = new Element < T >(current, current->GetPrev(), value);
                current->GetPrev()->SetNext(NewElement);
                current->SetPrev(NewElement);
                LinkedList < T > ::count++;
                return NewElement;
            }
        }
    }
}
};
bool CompareByInt(int Cur, int Val) {
    return Cur == Val;
}
bool FilterByInt(int Cur, int Val) {
    return Cur > Val;
}
int main() {
    return 0;
}