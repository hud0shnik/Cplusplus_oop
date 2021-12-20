#include <iostream>
#include <queue>
#include <ostream>

using namespace std;

class home
{
private:
    int Price;

public:

    int getPrice() const { return Price; }
    virtual void setPrice(int value) { Price = value; }
    home() { Price = rand() % 100000; }
    home(int Price) { Price = Price; }
};

ostream& operator<<(ostream& stream, const home& serial)
{
    stream << "Price: " << serial.getPrice();
    return stream;
}

template<typename T>
void print_queue(T& q) {
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

bool operator ==(home L, home B)
{
    if (L.getPrice() == B.getPrice())
        return true;
    else
        return false;
}

bool operator<(home L, home B)
{
    if (L.getPrice() < B.getPrice())
        return true;
    else
        return false;
}

class comparator
{
public:
    bool operator()(home& L, home& B)
    {
        return L.getPrice() < B.getPrice();
    }
};

int main()
{
    home home1, home2, home3;
    home homes[3] = { home1, home2, home3 };
    auto compare = [](home& L, home& b) { return L < b; };


    priority_queue<home> homeQueue;
    for (home n : homes)
        homeQueue.push(n);
    print_queue(homeQueue);

}
