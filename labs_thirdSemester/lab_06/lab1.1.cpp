#include <iostream>
#include <list>
#include <iterator>
using namespace std;

class Fraction {
  public:
    int num, denom;
  Fraction() {
    num = 1;
    denom = 1;
  }
  Fraction(int n, int d) {
    num = n;
    if (d == 0) {
      cout << "ERROR: ATTEMPTING TO DIVIDE BY ZERO" << endl;
      exit(0);
    } else
      denom = d;
  }
  friend ostream & operator << (std::ostream & stream,
    const Fraction & Elem) {
    stream << Elem.num << "/" << Elem.denom;
    return stream;
  }
};

bool operator < (Fraction L, Fraction R) {
  return (L.num / L.denom < R.num / R.denom);
}

template < class T >
  void push(list < T > & lst, T element) {
    auto it = lst.begin();
    while ((it != lst.end()) && (element > * it)) {
      * it++;
    }
    if (it != lst.end())
      lst.insert(it, element);
    else
      lst.push_back(element);
  }

template < class T >
  T pop(list < T > & father) {
    T temp = father.front();
    father.pop_front();
    return temp;
  }

bool P(Fraction element) {
  return (element.num < element.denom);
}

template < class T >
  list < T > filter(list < T > & lst, bool( * ptr)(T)) {
    list < T > son;
    auto it = lst.begin();
    while (it != lst.end()) {
      if (P( * it)) {
        son.push_back( * it);
      }
      * it++;
    }
    return son;
  }

template < class T >
  void print(list < T > & lst) {
    for (auto it = lst.begin(); it != lst.end();* it++) {
      cout << * it << " ";
    }
    cout << endl;
  }

int main() {
  return 0;
}