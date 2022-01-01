#include <iostream>
#include <queue>
#include <ostream>

using namespace std;

class program {
  private:
    int Price;

  public:

    int getPrice() const {
      return Price;
    }
  virtual void setPrice(int value) {
    Price = value;
  }
  program() {
    Price = rand() % 10000;
  }
  program(int Price) {
    Price = Price;
  }
};

ostream & operator << (ostream & stream,
  const program & serial) {
  stream << "Price: " << serial.getPrice();
  return stream;
}

bool operator == (program L, program B) {
  if (L.getPrice() == B.getPrice())
    return true;
  else
    return false;
}

bool operator < (program L, program B) {
  if (L.getPrice() < B.getPrice())
    return true;
  else
    return false;
}

template < typename T >
  void print_queue(T & q) {
    while (!q.empty()) {
      cout << q.top() << " ";
      q.pop();
    }
    std::cout << '\n';
  }

class comparator {
  public:
    bool operator()(program & L, program & B) {
      return L.getPrice() < B.getPrice();
    }
};

int main() {
  program s1, s2, s3;

  program Stad[3] = {
    s1,
    s2,
    s3
  };

  auto compare = [](program & L, program & b) {
    return L < b;
  };

  priority_queue < program > q;
  for (program n: Stad)
    q.push(n);
  print_queue(q);

  return 0;
}