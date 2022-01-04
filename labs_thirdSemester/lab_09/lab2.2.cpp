#include <iostream>
#include <queue>
#include <ostream>

using namespace std;

class locality
{
private:
    int Population;

public:

    int getPopulation() const { return Population; }
    virtual void setPopulation(int value) { Population = value; }
    locality() { Population = rand() % 100000; }
    locality(int Population) { Population = Population; }
};

ostream& operator<<(ostream& stream, const locality& serial)
{
    stream << "Population: " << serial.getPopulation();
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

bool operator ==(locality L, locality B)
{
    if (L.getPopulation() == B.getPopulation())
        return true;
    else
        return false;
}

bool operator<(locality L, locality B)
{
    if (L.getPopulation() < B.getPopulation())
        return true;
    else
        return false;
}

class comparator
{
public:
    bool operator()(locality& L, locality& B)
    {
        return L.getPopulation() < B.getPopulation();
    }
};

int main()
{
    locality locality1, locality2, locality3;
    locality localitys[3] = { locality1, locality2, locality3 };
    auto compare = [](locality& L, locality& b) { return L < b; };


    priority_queue<locality> localityQueue;
    for (locality n : localitys)
        localityQueue.push(n);
    print_queue(localityQueue);

}
