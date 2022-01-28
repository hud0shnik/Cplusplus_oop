#include <iostream>
#include <list>
#include <complex>
#include <iterator>
using namespace std;

template < class T >
void push(list < T >& lst, T element) {
    auto i = lst.begin();
    while ((i != lst.end()) && (element > *i)) {
        *i++;
    }

    if (i != lst.end())
        lst.insert(i, element);
    else
        lst.push_back(element);
}

template < class T >
void pop(list < T >& lst, T element) {
    lst.remove(element);
}

template < class T >
list < T > filter(list < T >& lst, bool(*ptr)(T)) {
    list < complex < int >> son;
    auto i = lst.begin();
    while (i != lst.end()) {
        if (P(*i)) {
            son.push_back(*i);
        }
        *i++;
    }
    return son;
}

template < class aviaCompany >
void print(list < aviaCompany >& father) {
    auto i = father.begin();
    for (; i != father.end(); ++i) {
        cout << *i;
    }
}

class aviaCompany {
private:
    int Reliability;
    int Lines;
    string Name;
    string Code;
    string Country;
    string WebSite;

public:
    aviaCompany() {
        Reliability = 0;
        Lines = 0;
        Name = "";
        Code = "";
        Country = "";
        WebSite = "";
    }

    aviaCompany(int reliability, int lines, string name, string code, string country, string webSite) {
        Reliability = reliability;
        Lines = lines;
        Name = name;
        Code = code;
        Country = country;
        WebSite = webSite;
    }

    aviaCompany(int reliability, int lines, string name) {
        Reliability = reliability;
        Lines = lines;
        Name = name;
    }

    bool operator > (aviaCompany& L) {
        bool res = false;
        if (Reliability > L.Reliability)
            res = true;
        else if (Reliability == L.Reliability)
            if (Lines > L.Lines)
                res = true;
            else if (Lines == L.Lines)
                if (Name > L.Name)
                    res = true;
                else if (Name == L.Name)
                    if (Code > L.Code)
                        res = true;
                    else if (Code == L.Code)
                        cout << "error";
        return res;
    }

    bool operator == (aviaCompany& L) {
        if ((Reliability == L.Reliability) & (Lines == L.Lines) & (Name == L.Name) & (Code == L.Code))
            return true;
        else
            return false;
    }

    friend ostream& operator << (ostream& result,
        const aviaCompany& obj);
};

template < class T >
T pop(list < T >& lst, int position = 0) {
    typename list < T > ::iterator p = lst.begin();
    advance(p, position);
    T value(*p);
    lst.erase(p);
    return value;
}

ostream& operator << (ostream& result,
    const aviaCompany& obj) {
    if (obj.Country == "" & obj.Code == "" & obj.WebSite == "") {
        result << "Reliability: " << obj.Reliability << " Lines: " << obj.Lines <<
            " Name: " << obj.Name;
        result << endl;
    }
    else {
        result << "Reliability: " << obj.Reliability << " Lines: " << obj.Lines <<
            " Name: " << obj.Name << " Code: " << obj.Code << " Sitizenship: " << obj.Country << " WebSite: " << obj.WebSite;
        result << endl;
    }

    return result;
}

template < class aviaCompany >
void bubble(list < aviaCompany >& father) {
    auto i = father.begin();
    auto i1 = father.begin();
    auto i2 = ++i1;
    for (; i != father.end(); ++i) {
        for (; i2 != (father.end()--); ++i2) {
            if (*i > *i2)
                swap(*i, *i2);
        }
    }
}

int main() {
    return 0;
}