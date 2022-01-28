#include <iostream>
#include <list>
#include <iterator>

using namespace std;

template < class T >
void push(list < T >& lst, T el) {
    auto it = lst.begin();
    while ((it != lst.end()) && (el > *it)) {
        *it++;
    }
    if (it != lst.end())
        lst.insert(it, el);
    else
        lst.push_back(el);
}

template < class T >
T pop(list < T >& f) {
    T temp = f.front();
    f.pop_front();
    return temp;
}

bool P(int el) {
    for (int i = 2; i < el; i++) {
        if (el % i == 0) {
            return false;
        }
    }
    return true;
}

template < class T >
list < T > filter(list < T >& lst, bool(*ptr)(T)) {
    list < T > s;
    auto it = lst.begin();
    while (it != lst.end()) {
        if (P(*it)) {
            s.push_back(*it);
        }
        *it++;
    }
    return s;
}

template < class T >
void print(list < T >& lst) {
    for (auto it = lst.begin(); it != lst.end(); *it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    return 0;
}