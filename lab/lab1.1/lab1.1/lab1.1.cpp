#include <iostream>
#include <list>
#include <complex>
#include <iterator>
// Интелектуальна собственность Дани
using namespace std;

/*Задание:
Тип T: Complex
Условие предиката P: Только числа с отрицательной действительной частью
*/

void push(list < complex < int >>& lst, complex < int > element) {
    auto it = lst.begin();
    while ((it != lst.end()) && (sqrt(real(element) * real(element) + imag(element) * imag(element)) > sqrt(real(*it) * real(*it) + imag(*it) * imag(*it)))) {
        *it++;
    }
    if (it != lst.end())
        lst.insert(it, element);
    else
        lst.push_back(element);
}

void pop(list < complex < int >>& lst, complex < int > element) {
    lst.remove(element);
}

bool P(complex < int > element) {
    if (real(element) < 0) {
        return true;
    }
    return false;
}

list < complex < int > > filter(list < complex < int > >& lst, bool(*ptr)(complex < int >)) {
    list < complex < int > > son;
    auto it = lst.begin();
    while (it != lst.end()) {
        if (P(*it)) {
            son.push_back(*it);
        }
        *it++;
    }
    return son;
}

void print(list < complex < int > >& lst) {
    for (auto it = lst.begin(); it != lst.end(); *it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    //Инициализируем два списка
    list < complex < int >> lst, lst2;

    //Заполняем первый список элементами
    for (int i = 0; i < 10; i += 2) {
        std::complex < int > compNum(i, 1);
        lst.push_back(compNum);
    }
    cout << "Before push(): " << endl;
    print(lst);

    //Пушим элементы в него
    push(lst, -5);
    push(lst, -3);
    push(lst, -44);
    push(lst, -10);
    cout << "After push(): " << endl;
    print(lst);

    //Удаляем элемент с вещественным числом -3
    cout << "After pop(): " << endl;
    pop(lst, -3);
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