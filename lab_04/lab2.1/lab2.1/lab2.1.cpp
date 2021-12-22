#include <map>
#include <iostream>
//Интеллектуальная собственность Дани
using namespace std;

struct Sportsman {
    int Medals;
    Sportsman() {
        Medals = rand() % 50;
    }
    friend std::ostream& operator << (std::ostream& stream,
        const Sportsman& Sportsman) {
        stream << "Medals: " << Sportsman.Medals;
        return stream;
    }
};

bool P(Sportsman s) {
    if (s.Medals > 25)
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

    for (; it != Map.end(); it++)    {
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

bool operator == (Sportsman prog1, Sportsman prog2) {
    if (prog1.Medals == prog2.Medals)
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
    map < string, Sportsman > sportsmans;
    Sportsman s1, s2, s3;

    sportsmans["First"] = s1;
    sportsmans["Second"] = s2;
    sportsmans["Third"] = s3;

    cout << "After findByKey() when key is \"First\": " << endl;
    auto s4 = FindByKey < string, Sportsman >(sportsmans, "First");
    cout << "Key: " << s4.first << ", value: " << s4.second << endl << endl;

    cout << "After findByValue() when value is \""<<s3.Medals<<"\": " << endl;
    auto s5 = FindByValue < string, Sportsman >(sportsmans, s3);
    cout << "Key: " << s5.first << ", value: " << s5.second << endl << endl;

    cout << "Before filter(): " << endl;
    Print(sportsmans);
    auto sportsmans2 = filter(sportsmans, P);

    cout << "After filter(): " << endl;
    Print(sportsmans2);
}