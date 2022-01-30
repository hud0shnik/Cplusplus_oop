#include <iostream>
#include <typeinfo>

using namespace std;

class Exception : public exception
{
protected:
	//сообщение об ошибке
	char* str;
public:
	Exception()
	{
		char s[] = "Unknown exception";
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}

	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << endl;
	}
};

class NOnumbers : public Exception
{
public:
	NOnumbers() : Exception("No numbers find") {}
};

template<class T>
class MyArrayParent
{
protected:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	T* ptr;
public:
	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100)
	{
		if (Dimension <= 0)
			throw NOnumbers();

		cout << "\nMyArrayParent constructor";
		ptr = new int[Dimension];
		capacity = Dimension;
		count = 0;
	}

	//Конструктором, принимающим и копирующим информацию из существующего массива.
	MyArrayParent(int SonCount, T* SonPtr)
	{
		count = SonCount;
		capacity = SonCount;

		ptr = new int[capacity];
		for (int i = 0; i < SonCount; i++)
			ptr[i] = SonPtr[i];
	}

	//деструктор
	~MyArrayParent(){}

	//обращение к полям
	int Capacity() { return capacity; }
	int Size() { return count; }
};

template<class T>
class MyArrayChild : public  MyArrayParent <T>
{
public:
	using MyArrayParent<T>::count;
	using MyArrayParent<T>::capacity;
	using MyArrayParent<T>::ptr;

	MyArrayChild(int len, T* arr) : MyArrayParent<T>(len, arr) {}
	MyArrayChild(int Dimension = 100) : MyArrayParent<T>(Dimension) { cout << "\nMyArrayChild constructor"; }
	~MyArrayChild() { }

	void push(T value)
	{
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
		}
	}

	//удаление элемента с конца
	void pop()
	{
		if (count > 0)
		{
			count--;
		}
	}

	MyArrayChild operator [] (int index)
	{
		return ptr[index];
	}

	int find(T val)
	{
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] == val)
			{
				return i;
			}
		}

	}

	MyArrayChild arrayUnique() const
	{
		int count1 = count;
		T* ptr1 = new T[count1];

		for (int i = 0; i < count1; i++)
			ptr1[i] = ptr[i];


		for (int i = 0; i < count1; i++)
		{
			for (int j = i + 1; j < count1 ; j++)
			{
				if (ptr1[i] == ptr1[j]) 
				{
					for (int k = j; k < count1 - 1; k++)
					{
						
						ptr1[k] = ptr1[k + 1];
					}
					count1--; 

					if (ptr1[i] == ptr1[j]) 
					{
						j--;   
					}
				}
			}
		}
		MyArrayChild Rez(count1, ptr1);
		return Rez;
	}

	void print()
	{
		cout << "\nMyArrParent, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}

	friend ostream& operator<< (ostream& ustream, const MyArrayChild& obj);
};

template <class V>
ostream& operator << (ostream& ustream, const MyArrayChild <V> & obj)
{
	for (int i = 0; i < obj.count; i++)
	{
			ustream << obj.ptr[i] << " ";
		ustream << "\\n";
	}
	return ustream;
}



int main()
{
	try
	{
		srand((unsigned)time(NULL));
		const int ptr_size = 10;
		int arr[ptr_size];
		int value;
		int counter = 0;
		while (counter < ptr_size)
		{
			value = rand() % 10;

			if (value >= 1)
			{
				arr[counter] = value;
				counter++;
			}
		}

		MyArrayChild <int> B1(ptr_size, arr);

		cout << "Array" << endl;
		B1.print();

		cout << " pop work" << endl;
		B1.pop();

		B1.print();

		cout << " push work" << endl;
		B1.push(4);

		B1.print();

		cout << endl << " looking element has index:" << B1.find(4) << endl;

		MyArrayChild <int> B2;

		B2 = B1.arrayUnique();
		cout << "Array with unque numbers";
		B2.print();
	}

	catch (NOnumbers e)
	{
		cout << "\nException has been caught: "; e.print();
		cout << endl;
	}

	return 0;
}