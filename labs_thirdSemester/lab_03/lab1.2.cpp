#include <iostream>
#include <list>
#include <iterator>
using namespace std;

template < class T >
void push(list < T >& lst, T el) {
    auto i = lst.begin();
    while ((i != lst.end()) && (el > *i)) {
        *i++;
    }

    if (i != lst.end())
        lst.insert(i, el);
    else
        lst.push_back(el);
}

template < class T >
void pop(list < T >& lst, T el) {
    lst.remove(el);
}

template < class T >
list < T > filter(list < T >& lst, bool(*ptr)(T)) {
    list < complex < int >> n;
    auto i = lst.begin();
    while (i != lst.end()) {
        if (P(*i)) {
            n.push_back(*i);
        }
        *i++;
    }
    return n;
}

template < class smartPhone >
void print(list < smartPhone >& f) {
    auto i = f.begin();
    for (; i != f.end(); ++i) {
        cout << *i;
    }
}

class smartPhone {
private:
    int Price;
    int Camera;
    string Name;
    string Size;
    string Battery;

public:
    smartPhone() {
        Price = 0;
        Camera = 0;
        Name = "";
        Size = "";
        Battery = "";
    }

    smartPhone(int price, int camera, string name, string size, string Battery, string webSite) {
        Price = price;
        Camera = camera;
        Name = name;
        Size = size;
        Battery = Battery;
    }

    smartPhone(int price, int camera, string name) {
        Price = price;
        Camera = camera;
        Name = name;
    }

    bool operator > (smartPhone& L) {
        bool res = false;
        if (Price > L.Price)
            res = true;
        else if (Price == L.Price)
            if (Camera > L.Camera)
                res = true;
            else if (Camera == L.Camera)
                if (Name > L.Name)
                    res = true;
                else if (Name == L.Name)
                    if (Size > L.Size)
                        res = true;
                    else if (Size == L.Size)
                        cout << "error";
        return res;
    }

    bool operator == (smartPhone& L) {
        if ((Price == L.Price) & (Camera == L.Camera) & (Name == L.Name) & (Size == L.Size))
            return true;
        else
            return false;
    }

    friend ostream& operator << (ostream& result,
        const smartPhone& obj);
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
    const smartPhone& obj) {
    if (obj.Battery == "" & obj.Size == "") {
        result << "Price: " << obj.Price << " Camera: " << obj.Camera <<
            " Name: " << obj.Name;
        result << endl;
    }
    else {
        result << "Price: " << obj.Price << " Camera: " << obj.Camera <<
            " Name: " << obj.Name << " Size: " << obj.Size << " Battery: " << obj.Battery;
        result << endl;
    }

    return result;
}

template < class smartPhone >
void bubble(list < smartPhone >& f) {
    auto i = f.begin();
    auto i1 = f.begin();
    auto i2 = ++i1;
    for (; i != f.end(); ++i) {
        for (; i2 != (f.end()--); ++i2) {
            if (*i > *i2)
                swap(*i, *i2);
        }
    }
}

int main() {
    return 0;
}