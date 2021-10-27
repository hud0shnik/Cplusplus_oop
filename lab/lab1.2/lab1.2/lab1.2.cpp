#include <iostream>
#include <list>
#include <complex>
#include <iterator>
 // Интелектуальна собственность Дани
using namespace std;

/*Задание:
Тип T: Спортсмен». 

Приоритет: Количество  медалей; 
возраст  (по  возраста-
нию);  фамилия  и  имя 
(по возрастанию)
*/

template < class T >
  void push(list < T > & lst, T element) {
    auto it = lst.begin();
    while ((it != lst.end()) && (element > * it)) {
      * it++;
    }

    if (it != lst.end())
      lst.insert(it, element);
    else
      lst.push_back(element);
  }

template < class T >
  void pop(list < T > & lst, T element) {
    lst.remove(element);
  }

template < class T >
  bool P(T element) {
    if (real(element) < 0) {
      return true;
    }
    return false;
  }

template < class T >
  list < T > filter(list < T > & lst, bool( * ptr)(T)) {
    list < complex < int > > son;
    auto it = lst.cbegin();
    while (it != lst.cend()) {
      if (P( * it)) {
        son.push_back( * it);
      }
      * it++;
    }
    return son;
  }

template < class sportsman >
  void print(list < sportsman > & father) {
    auto it = father.cbegin();
    for (; it != father.cend(); ++it) {
      cout << * it << " ";
    }
  }

class sportsman {
  private:
    int Medals;
  int Age;
  string Name;

  public:

    sportsman() {
      Medals = 0;
      Age = 0;
      Name = "";
    }

  sportsman(int medals, int age, string name) {
    Medals = medals;
    Age = age;
    Name = name;
  }

  bool operator > (sportsman & L) {
    bool res = false;
    if (Medals > L.Medals)
      res = true;
    else if (Medals == L.Medals)
      if (Age > L.Age)
        res = true;
      else if (Age == L.Age)
      if (Name > L.Name)
        res = true;
      else if (Name == L.Name)
      cout << "error";

    return res;
  }

  bool operator == (sportsman & L) {
    if ((Medals == L.Medals) & (Age == L.Age) & (Name == L.Name))
      return true;
    else
      return false;
  }

  friend ostream & operator << (ostream & ustream,
    const sportsman & obj);
};

template < class T >
  T pop(list < T > & lst, int position = 0) {
    typename list < T > ::iterator p = lst.begin();
    advance(p, position);
    T value( * p);
    lst.erase(p);
    return value;
  }

ostream & operator << (ostream & ustream,
  const sportsman & obj) {
  ustream << "Medals: " << obj.Medals << " Age: " << obj.Age <<
    " Name: " << obj.Name;
  ustream << endl;

  return ustream;
}

template < class sportsman >
  void sort(list < sportsman > & father) {
    auto it = father.begin();
    auto it1 = father.begin();
    auto it2 = ++it1;
    for (; it != father.end(); ++it) {
      for (; it2 != (father.end() --); ++it2) {
        if ( * it > * it2)
          swap( * it, * it2);
      }
    }
  }

int main() {

  sportsman first(99, 28, "Aboba");
  sportsman second(13, 28, "Arnold");
  sportsman third(4, 18, "Sanya");

  list < sportsman > example;
  example.push_back(first);
  example.push_back(second);
  example.push_back(third);

  print(example);

  sort(example);

  print(example);
  cout << endl;

  cout << pop(example) << endl;

  print(example);

  return 0;
}