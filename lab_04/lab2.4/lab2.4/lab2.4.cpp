#include <iostream>
#include <cassert>

using namespace std;

class Sportsman {
private:
    string Name = "Unknown";
    string LastName = "Unknown";
    int Age = 0;
    string Sitizenship = "Unknown";
    string Sport = "Unknown";
    int Medals = 0;
public:
    friend ostream& operator << (ostream& stream,
        const Sportsman& S);
    void SetMedals(int Medals) {
        Medals = Medals;
    }
    void SetAge(double Age) {
        Age = Age;
    }
    void SetName(string name) {
        Name = name;
    }

    bool operator == (const Sportsman& s) {
        bool f = true;
        if (Name == s.Name)
            f = false;
        if (Age == s.Age)
            f = false;
        if (LastName == s.LastName)
            f = false;
        if (Medals == s.Medals)
            f = false;
        if (Sitizenship == s.Sitizenship)
            f = false;
        if (Sport == s.Sport)
            f = false;
        return f;
    }

    bool operator > (const Sportsman& s) {
        if (Medals > s.Medals)
            return true;
        if (Medals < s.Medals)
            return false;
        if (Medals == s.Medals) {
            if (Age > s.Age)
                return true;
            if (Age < s.Age)
                return false;
            if (Age == s.Age) {
                if (Name > s.Name)
                    return true;
                if (Name < s.Name)
                    return false;
            }
        }
        return false;
    }

    bool operator < (const Sportsman& s) {
        if (Medals < s.Medals)
            return true;
        if (Medals > s.Medals)
            return false;
        if (Medals == s.Medals) {
            if (Age < s.Age)
                return true;
            if (Age > s.Age)
                return false;
            if (Age == s.Age) {
                if (Name < s.Name)
                    return true;
                if (Name > s.Name)
                    return false;
            }
        }
        return false;
    }
};

template < class T >
class Node {
private:
    T value;

public:
    //установить данные в узле
    T getValue() {
        return value;
    }
    void setValue(T v) {
        value = v;
    }
    //сравнение узлов
    int operator < (Node N) {
        return (value < N.getValue());
    }
    int operator > (Node N) {
        return (value > N.getValue());
    }
    int operator <= (Node N) {
        return (value <= N.getValue());
    }
    int operator >= (Node N) {
        return (value >= N.getValue());
    }
    //вывод содержимого одного узла
    void print() {
        cout << value;
    }
    T operator * () {
        return value;
    }
    friend ostream& operator << (ostream& s, Node < T > el) {
        s << el.getValue() << std::endl;
        return s;
    }

};
template < class T >
void print(Node < T >* N) {
    cout << N->getValue() << "\n";
}
//куча (heap)
template < class T >
class Heap {
private:
    //массив
    Node < T >* arr;
    //сколько элементов добавлено
    int len;
    //сколько памяти выделено
    int size;

public:
    //доступ к вспомогательным полям кучи и оператор индекса
    int getCapacity() {
        return size;
    }
    int getCount() {
        return len;
    }
    Node < T >& operator[](int index) {
        assert(index >= 0 || index < len); //?
        return arr[index];
    }
    //конструктор
    Heap < T >(int MemorySize = 100) {
        arr = new Node < T >[MemorySize];
        len = 0;
        size = MemorySize;
    }

    //поменять местами элементы arr[index1], arr[index2]
    void Swap(int index1, int index2) {
        assert(index1 >= 0 || index1 < len);
        assert(index2 >= 0 || index2 < len);

        //здесь нужна защита от дурака
        Node < T > temp;
        temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }
    //скопировать данные между двумя узлами
    void Copy(Node < T >* dest, Node < T >* source) {
        dest->setValue(source->getValue());
    }
    //функции получения левого, правого дочернего элемента, родителя или их индексов в
    //массиве
    Node < T >* GetLeftChild(int index) {
        assert(index >= 0 || index * 2 + 1 < len);
        return &arr[index * 2 + 1];
    }
    Node < T >* GetRightChild(int index) {
        assert(index >= 0 || index * 2 + 2 < len);
        //здесь нужна защита от дурака
        return &arr[index * 2 + 2];
    }
    Node < T >* GetParent(int index) {
        assert(index >= 0 || index < len);
        //здесь нужна защита от дурака
        return (index % 2 == 0) ? &arr[index / 2 - 1] : &arr[index / 2];

    }
    int GetLeftChildIndex(int index) {
        assert(index >= 0 || index * 2 + 1 < len);
        return index * 2 + 1;
    }
    int GetRightChildIndex(int index) {
        assert(index >= 0 || index * 2 + 2 < len);
        return index * 2 + 2;
    }
    int GetParentIndex(int index) {
        assert(index >= 0 || index < len);
        return (index % 2 == 0) ? index / 2 - 1 : index / 2;
    }
    //просеять элемент вверх
    void SiftUp(int index = -1) {
        if (index == -1)
            index = len - 1;
        int parent = GetParentIndex(index);
        int index2 = GetLeftChildIndex(parent);
        if (index2 == index)
            index2 = GetRightChildIndex(parent);
        int max_index = index;
        if (index < len && index2 < len && parent >= 0) {
            if (arr[index] > arr[index2])
                max_index = index;
            if (arr[index] < arr[index2])
                max_index = index2;
        }
        if (parent < len && parent >= 0 && arr[max_index] > arr[parent]) {
            Swap(parent, max_index);
            SiftUp(parent);
        }
    }
    //добавление элемента - вставляем его в конец массива и просеиваем вверх
    void SiftDown(int index = -1) {
        bool flag = true;
        if (index == -1)
            index = 0;
        int indexL = GetLeftChildIndex(index);
        int indexR = GetRightChildIndex(index);
        int indexMax = index;
        if (indexL < len && indexR < len) {
            if (arr[indexL] >= arr[indexR])
                indexMax = indexL;
            else
                indexMax = indexR;
        }
        else if (indexL < len) {
            indexMax = indexL;
        }
        else {
            flag = false;
        }
        if (arr[index] < arr[indexMax] && flag) {
            Swap(index, indexMax);
            SiftDown(indexMax);
        }
    }
    Node < T >* ExtractMax() {
        assert(len > 0);
        Node < T >* tmp = new Node < T >;
        Copy(tmp, &arr[0]);
        Copy(&arr[0], &arr[len - 1]);
        len--;

        SiftDown();
        return tmp;
    }

    void Add(T v) {
        Node < T >* N = new Node < T >;
        N->setValue(v);
        Add(N);
    }

    void Add(Node < T >* N) {
        if (len < size) {
            Copy(&arr[len], N);
            len++;
            SiftUp();
        }
    }
    void Straight(void(*f)(Node < T >*)) {
        int i;
        for (i = 0; i < len; i++) {
            f(&arr[i]);
        }
    }
    void PreOrder(void(*f)(Node < T >*), int index = 0) {
        if (index >= 0 && index < len)
            f(&arr[index]);
        if (GetLeftChildIndex(index) < len)
            PreOrder(f, GetLeftChildIndex(index));
        if (GetRightChildIndex(index) < len)
            PreOrder(f, GetRightChildIndex(index));
    }
    void InOrder(void(*f)(Node < T >*), int index = 0) {
        if (GetLeftChildIndex(index) < len)
            PreOrder(f, GetLeftChildIndex(index));
        if (index >= 0 && index < len)
            f(&arr[index]);
        if (GetRightChildIndex(index) < len)
            PreOrder(f, GetRightChildIndex(index));
    }

    void HeapOut() {
        Heap < T > tmp;
        tmp.len = this->len;
        tmp.size = this->size;
        for (int i = 0; i < len; i++) {
            Copy(&(tmp.arr[i]), &arr[i]);
        }
        while (tmp.getCount() != 0) {
            cout << *(tmp.ExtractMax()) << endl;
        }
    }

    void Print() {
        for (int i = 0; i < len; i++) {
            cout << arr[i];
        }
    }
};

int main() {
    Heap < Sportsman > SportsmansHeap;
    Sportsman s1, s2, s3, s4, s5;
    SportsmansHeap.Add(s1);
    SportsmansHeap.Add(s2);
    SportsmansHeap.Add(s3);
    SportsmansHeap.Add(s4);
    SportsmansHeap.Add(s5);

    while (SportsmansHeap.getCount() != 0) {
        cout << *(SportsmansHeap.ExtractMax()) << endl;
    }
    SportsmansHeap.HeapOut();

    void(*f_ptr)(Node < Sportsman > *);
    f_ptr = print;
    SportsmansHeap.Straight(f_ptr);

}