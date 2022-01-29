#include <iostream>
#include <queue>
#include <ostream>

using namespace std;

class SmartPhone
{
private:
    int Price;

public:

    int getPrice() const { return Price; }
    virtual void setPrice(int value) { Price = value; }
    SmartPhone() { Price = rand() % 1000; }
    SmartPhone(int Price) { Price = Price; }
};

ostream& operator<<(ostream& stream, const SmartPhone& serial)
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

bool operator ==(SmartPhone L, SmartPhone B)
{
    if (L.getPrice() == B.getPrice())
        return true;
    else
        return false;
}

bool operator<(SmartPhone L, SmartPhone B)
{
    if (L.getPrice() < B.getPrice())
        return true;
    else
        return false;
}

class comparator
{
public:
    bool operator()(SmartPhone& L, SmartPhone& B)
    {
        return L.getPrice() < B.getPrice();
    }
};

int main()
{
    SmartPhone SmartPhone1, SmartPhone2, SmartPhone3;
    SmartPhone SmartPhones[3] = { SmartPhone1, SmartPhone2, SmartPhone3 };
    auto compare = [](SmartPhone& L, SmartPhone& b) { return L < b; };


    priority_queue<SmartPhone> SmartPhoneQueue;
    for (SmartPhone n : SmartPhones)
        SmartPhoneQueue.push(n);
    print_queue(SmartPhoneQueue);

}
