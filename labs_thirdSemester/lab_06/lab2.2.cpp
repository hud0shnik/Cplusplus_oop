#include <iostream>
#include <queue>
#include <ostream>

using namespace std;

class AviaCompany {
private:
    int Lines;

public:

    int getLines() const {
        return Lines;
    }
    virtual void setLines(int value) {
        Lines = value;
    }
    AviaCompany() {
        Lines = rand() % 100000;
    }
    AviaCompany(int Lines) {
        Lines = Lines;
    }
};

ostream& operator << (ostream& stream,
    const AviaCompany& serial) {
    stream << "Lines: " << serial.getLines();
    return stream;
}

bool operator == (AviaCompany L, AviaCompany B) {
    if (L.getLines() == B.getLines())
        return true;
    else
        return false;
}

bool operator < (AviaCompany L, AviaCompany B) {
    if (L.getLines() < B.getLines())
        return true;
    else
        return false;
}

template < typename T >
void print_queue(T& q) {
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

class comparator {
public:
    bool operator()(AviaCompany& L, AviaCompany& B) {
        return L.getLines() < B.getLines();
    }
};

int main() {
    AviaCompany company1, company2, company3;

    AviaCompany Arr[3] = {
      company1,
      company2,
      company3
    };

    auto compare = [](AviaCompany& L, AviaCompany& b) {
        return L < b;
    };

    priority_queue < AviaCompany > q;
    for (AviaCompany n : Arr)
        q.push(n);
    print_queue(q);

    return 0;
}