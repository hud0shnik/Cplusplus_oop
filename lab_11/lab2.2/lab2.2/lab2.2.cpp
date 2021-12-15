#include <iostream>
#include <queue>
#include <ostream>

using namespace std;

class film
{
private:
    int Income;

public:

    int getIncome() const { return Income; }
    virtual void setIncome(int value) { Income = value; }
    film() { Income = rand() % 100000; }
    film(int Income) { Income = Income; }
};

ostream& operator<<(ostream& stream, const film& serial)
{
    stream << "Income: " << serial.getIncome();
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

bool operator ==(film L, film B)
{
    if (L.getIncome() == B.getIncome())
        return true;
    else
        return false;
}

bool operator<(film L, film B)
{
    if (L.getIncome() < B.getIncome())
        return true;
    else
        return false;
}

class comparator
{
public:
    bool operator()(film& L, film& B)
    {
        return L.getIncome() < B.getIncome();
    }
};

int main()
{
    film film1, film2, film3;

    film films[3] = { film1, film2, film3 };

    auto compare = [](film& L, film& b) { return L < b; };


    priority_queue<film> filmQueue;
    for (film n : films)
        filmQueue.push(n);
    print_queue(filmQueue);

}
