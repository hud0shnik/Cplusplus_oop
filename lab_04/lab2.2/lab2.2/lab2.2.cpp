#include <iostream>
#include <queue>
#include <ostream>
//Интеллектуальная собственность Дани
using namespace std;

class sportsman {
private:
    int Medals;
public:

    int getMedals() const {
        return Medals;
    }
    virtual void setMedals(int value) {
        Medals = value;
    }
    sportsman() {
        Medals = rand() % 10;
    }
};

bool operator == (sportsman L, sportsman R) {
    if (L.getMedals() == R.getMedals()) {
        return true;
    }
    return false;
}

bool operator < (sportsman L, sportsman R) {
    if (L.getMedals() < R.getMedals()) {
        return true;
    }
    return false;
}
ostream& operator << (ostream& stream,
    const sportsman& s) {
    stream << "Medals: " << s.getMedals();
    return stream;
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
    bool operator()(sportsman& L, sportsman& R) {
        return L.getMedals() < R.getMedals();
    }
};

int main() {
    sportsman first, second, third;
    first.setMedals(777);

    sportsman m[3] = {
      first,
      second,
      third
    };

    auto compare = [](sportsman& L, sportsman& R) {
        return L < R;
    };

    priority_queue < sportsman > queue;
    for (int i = 0; i < 3; i++) {
        queue.push(m[i]);
    }

    print_queue(queue);
}