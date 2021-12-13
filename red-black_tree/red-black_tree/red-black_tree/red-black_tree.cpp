#include <iostream>

using namespace std;

int tabs = 0; //Для создания отступов
int kol_vo = 0;
//Кол-во отступов высчитывается по кол-ву рекурсивного вхождения при выводе в фукцию print

//Структура ветки
struct Branch {
    int Data; //Поле данных
    Branch* LeftBranch; //УКАЗАТЕЛИ на соседние веточки
    Branch* RightBranch;
};

//Функция внесения данных
void Add(int aData, Branch*& aBranch) {
    //Если ветки не существует
    if (!aBranch) { //создадим ее и зададим в нее данные
        aBranch = new Branch;
        aBranch->Data = aData;
        aBranch->LeftBranch = 0;
        aBranch->RightBranch = 0;
        return;
    }
    else //Иначе сверим вносимое
        if (aBranch->Data > aData) { //Если оно меньше того, что в этой ветке - добавим влево
            Add(aData, aBranch->LeftBranch);
        }
        else { //Иначе в ветку справа
            Add(aData, aBranch->RightBranch);
        };
}

//Функция вывода дерева
void print(Branch* aBranch) {
    if (!aBranch) return; //Если ветки не существует - выходим. Выводить нечего
    tabs += 5; //Иначе увеличим счетчик рекурсивно вызванных процедур
    //Который будет считать нам отступы для красивого вывода

    print(aBranch->LeftBranch); //Выведем ветку и ее подветки слева

    for (int i = 0; i < tabs; i++) cout << " "; //Потом отступы
    cout << aBranch->Data << endl; //Данные этой ветки

    print(aBranch->RightBranch); //И ветки, что справа

    tabs -= 5; //После уменьшим кол-во отступов
    return;
}

void pr_obh(Branch*& aBranch) {
    if (NULL == aBranch) return; //Если дерева нет, выходим

    cout << aBranch->Data << endl; //Посетили узел
    pr_obh(aBranch->LeftBranch); //Обошли левое поддерево   
    pr_obh(aBranch->RightBranch); //Обошли правое поддерево
}

int kol_ch(Branch*& aBranch) {
    if (NULL == aBranch) return 0; //Если дерева нет, выходим

    if (aBranch->Data % 2 == 0) {
        kol_vo++;
    }
    kol_ch(aBranch->LeftBranch); //Обошли левое поддерево   
    kol_ch(aBranch->RightBranch); //Обошли правое поддерево
    return kol_vo;
}

int summ_k(Branch*& aBranch, int k) {
    int sum = 0;
    if ((aBranch != NULL) && (k > 0)) {
        sum += summ_k(aBranch->LeftBranch, k - 1);
        sum += aBranch->Data;
        sum += summ_k(aBranch->RightBranch, k - 1);
    }
    return sum;
}
void add_elem(int aData, Branch*& aBranch) {
    if (!aBranch) {
        aBranch = new Branch;
        aBranch->Data = aData;
        aBranch->LeftBranch = 0;
        aBranch->RightBranch = 0;
        return;
    }
    else {
        if (aData < aBranch->Data) {
            add_elem(aData, aBranch->LeftBranch);
        }
        else if (aData > aBranch->Data) {
            add_elem(aData, aBranch->RightBranch);
        }
    }
}

void is_Empty(Branch*& aBranch) {
    if (!aBranch) {
        cout << "Дерево пустое...";
    }
    else {
        cout << "Дерево не пустое...";
    }
}

void FreeTree(Branch* aBranch) {
    if (!aBranch) return;
    FreeTree(aBranch->LeftBranch);
    FreeTree(aBranch->RightBranch);
    delete aBranch;
    return;
}

Branch* del_elem(Branch*& aBranch, int aData) {
    if (aBranch == NULL)
        return aBranch;

    if (aData == aBranch->Data) {

        Branch* tmp;
        if (aBranch->RightBranch == NULL)
            tmp = aBranch->LeftBranch;
        else {

            Branch* ptr = aBranch->RightBranch;
            if (ptr->LeftBranch == NULL) {
                ptr->LeftBranch = aBranch->LeftBranch;
                tmp = ptr;
            }
            else {

                Branch* pmin = ptr->LeftBranch;
                while (pmin->LeftBranch != NULL) {
                    ptr = pmin;
                    pmin = ptr->LeftBranch;
                }
                ptr->LeftBranch = pmin->RightBranch;
                pmin->LeftBranch = aBranch->LeftBranch;
                pmin->RightBranch = aBranch->RightBranch;
                tmp = pmin;
            }
        }

        delete aBranch;
        return tmp;
    }
    else if (aData < aBranch->Data)
        aBranch->LeftBranch = del_elem(aBranch->LeftBranch, aData);
    else
        aBranch->RightBranch = del_elem(aBranch->RightBranch, aData);
    return aBranch;
}

int main() {
    setlocale(LC_ALL, "rus");
    Branch* Root = 0;
    int vel;
    int element;
    int k;

    cout << "Введите кол-во элементов для будущего дерева: ";
    cin >> vel;
    cout << endl;

    cout << "Проверим дерево на пустоту до его заполнения: " << endl;
    is_Empty(Root);
    cout << endl;

    for (int i = 0; i < vel; i++) {
        Add(rand() % 100, Root);
    }

    cout << "Проверим дерево на пустоту после его заполнения: " << endl;
    is_Empty(Root);
    cout << endl;

    cout << "Вывод бинарного дерева: " << endl;
    print(Root);
    cout << endl;

    cout << "Прямой обход бинарного дерева: " << endl;
    pr_obh(Root);
    cout << endl;

    cout << "Добавим новый элемент в бинарное дерево:" << endl;
    cout << "Введите новый элемент: ";
    cin >> element;
    add_elem(element, Root);

    cout << "Вывод бинарного дерева: " << endl;
    print(Root);
    cout << endl;

    cout << "Удалим элемент из бинарного дерева:" << endl;
    cout << "Введите нэлемент: ";
    cin >> element;
    del_elem(Root, element);

    cout << "Вывод бинарного дерева: " << endl;
    print(Root);
    cout << endl;

    cout << "Посчитаем кол-во четных элементов в дереве: ";
    cout << kol_ch(Root) << endl;

    cout << "Посчитаем сумму элементов в дереве на уровне ";
    cin >> k;
    cout << summ_k(Root, k) << endl;

    FreeTree(Root);
    cout << "Вся динамическая память очищена..." << endl;

    return 0;
}