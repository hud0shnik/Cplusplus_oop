#include <iostream>
#include <list>
#include <complex>
#include <iterator>
// Интелектуальна собственность Дани
using namespace std;

/*Вариант 4
Тип T: Complex
Условие предиката P: Только числа с отрицательной действительной частью
*/

template<class T>
void push(list <T>& lst, T element) {
    auto it = lst.begin();
    while ((it != lst.end()) && (sqrt(real(element) * real(element) + imag(element) * imag(element)) > sqrt(real(*it) * real(*it) + imag(*it) * imag(*it)))) {
        *it++;
    }
    if (it != lst.end())
        lst.insert(it, element);
    else
        lst.push_back(element);
}

template<class T>
void pop(list <T>& lst, T element) {
    lst.remove(element);
}

template<class T>
bool P(T element) {
    if (real(element) < 0) {
        return true;
    }
    return false;
}

template<class T>
list < T> filter(list < T >& lst, bool(*ptr)(T)) {
    list<T> son;
    auto it = lst.begin();
    while (it != lst.end()) {
        if (P(*it)) {
            son.push_back(*it);
        }
        *it++;
    }
    return son;
}

template<class T>
void print(list <T>& lst) {
    for (auto it = lst.begin(); it != lst.end(); *it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    //Инициализируем два списка
    list < complex < int >> lst, lst2;
    complex <int> first, second;
    first = -3;
    second = -11;
    //Заполняем первый список элементами
    for (int i = 0; i < 10; i += 2) {
        std::complex < int > compNum(i, 0);
        lst.push_back(compNum);
    }
    cout << "Before push(): " << endl;
    print(lst);
    //Пушим элементы в него
    push(lst, first);
    push(lst, second);
    cout << "After push(): " << endl;
    print(lst);

    //Удаляем элемент с вещественным числом -3
    cout << "After pop(): " << endl;
    pop(lst, first);
    print(lst);

    //Фильтруем первый список, и записываем результат во второй 
    bool(*ptr)(complex < int >);
    ptr = P;
    lst2 = filter(lst, ptr);
    cout << "\n";

    //Выводим результат
    cout << "After filter(): " << endl;
    print(lst2);
    cout << "That's all!" << endl;
    return 0;
}