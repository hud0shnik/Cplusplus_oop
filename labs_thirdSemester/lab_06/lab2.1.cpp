#include <map>
#include <iostream>
using namespace std;

struct AviaCompany {
    int Lines;
    AviaCompany() {
        Lines = rand() % 50000;
    }
    friend std::ostream& operator << (std::ostream& stream,
        const AviaCompany& AviaCompany) {
        stream << "Lines: " << AviaCompany.Lines;
        return stream;
    }
};

bool P(AviaCompany s) {
    if (s.Lines > 25000)
        return true;
    return false;
}

template < class TKey, class TValue >
pair < TKey, TValue > FindByKey(const map < TKey, TValue >& Map, TKey key) {
    auto res = Map.find(key);

    if (res != Map.end()) {
        return pair < TKey, TValue >(res->first, res->second);
    }
    return pair < TKey, TValue >(Map.end()->first, Map.end()->second);

}

template < class TKey, class TValue >
pair < TKey, TValue > FindByValue(const map < TKey, TValue >& Map, TValue value) {
    auto it = Map.begin();

    for (; it != Map.end(); it++) {
        if (it->second == value)
            return pair < TKey, TValue >(it->first, it->second);
    }
    return pair < TKey, TValue >(Map.end()->first, Map.end()->second);
}

template < class TKey, class TValue >
void Print(const map < TKey, TValue >& Map) {
    auto it_m = Map.begin();

    for (; it_m != Map.end(); it_m++)
        cout << "Key: " << it_m->first << ", Value: " << it_m->second << endl;
    cout << endl;
}

bool operator == (AviaCompany comp1, AviaCompany comp2) {
    if (comp1.Lines == comp2.Lines)
        return true;
    return false;
}

template < class TKey, class TValue >
std::map < TKey, TValue > filter(std::map < TKey, TValue >& map, bool(*func)(TValue x)) {
    std::map < TKey, TValue > result;

    for (auto element : map) {
        if (func(element.second)) {
            result[element.first] = element.second;
        }
    }
    return result;
}

int main() {
    return 0;
}