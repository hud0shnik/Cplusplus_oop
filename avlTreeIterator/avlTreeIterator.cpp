//#include "stdafx.h"
#include <iostream>

using namespace std;
//узел
template<class T>
class Node
{
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	T data;

	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;

	//переменная, необходимая для поддержания баланса дерева
	int height;
public:
	//доступные извне переменные и функции
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }

	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }

	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }

	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<T>(T n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}

	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		data = 0;
		height = 1;
	}


	virtual void print()
	{
		cout << "\n" << data;
	}

	virtual void setHeight(int h)
	{
		height = h;
	}

	template<class T> friend ostream& operator<< (ostream& stream, Node<T>& N);
};

template<class T>
ostream& operator<< (ostream& stream, Node<T>& N)
{
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}
template<class T>
void print(Node<T>* N) { cout << "\n" << N->getData(); }

template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;
public:
	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { root = NULL; }

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, root);
	}

	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		if (N == NULL) return NULL;
		if (root == NULL)
		{
			root = N;
			return N;
		}

		if (Current->getData() > N->getData())
		{
			//идем влево
			if (Current->getLeft() != NULL)
				Current->setLeft(Add_R(N, Current->getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getData() < N->getData())
		{
			//идем вправо
			if (Current->getRight() != NULL)
				Current->setRight(Add_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getData() == N->getData())
			//нашли совпадение
			;
		//для несбалансированного дерева поиска
		return Current;
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* Add(T n)
	{
		Node<T>* N = new Node<T>(n);
		return Add_R(N);
	}

	//удаление узла
	virtual void Remove(Node<T>* N)
	{ }

	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;

		if (Current == NULL)
			Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();

		return Current;
	}

	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		//минимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) return NULL;

		if (Current == NULL)
			Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();

		return Current;
	}


	//поиск узла в дереве
	virtual Node<T>* Find(T data)
	{
		if (root == NULL) return NULL;
		return Find_R(data, root);
	}

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T>* Find_R(T data, Node<T>* Current)
	{
		//база рекурсии
		if (Current == NULL) return NULL;

		if (Current->getData() == data) return Current;

		//рекурсивный вызов
		if (Current->getData() > data) return Find_R(data, Current->getLeft());

		if (Current->getData() < data) return Find_R(data, Current->getRight());


	}

	//три обхода дерева
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}
};

template<typename ValueType>
class TreeIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:

public:
	TreeIterator() { ptr = NULL; T = NULL; }
	//ListIterator(ValueType* p) { ptr = p; }
	TreeIterator(Tree<ValueType>* t, Node<ValueType>* p) { T = t; ptr = p; }
	TreeIterator(const TreeIterator& it) { T = it.T; ptr = it.ptr; }


	bool operator!=(TreeIterator const& other) const { return ptr != other.ptr; }
	bool operator==(TreeIterator const& other) const { return ptr == other.ptr; }
	Node<ValueType>& operator*()
	{
		//if(otr==NULL) исключение
		return *ptr;
	}
	TreeIterator& operator++()
	{
		if (ptr == NULL)
			return *this;
		if (ptr->getRight() != NULL) {
			ptr = T->Min(ptr->getRight());
			return *this;
		}
		Node<ValueType>* Current = ptr;
		while (true) {
			if (Current->getParent() == NULL)	return *this;
			
			if (Current->getParent()->getLeft()==Current){
				ptr = Current->getParent();
				return *this;
			}
			Current = Current->getParent();
		}
	}

	TreeIterator& operator++(int v)
	{
		if (ptr == NULL) {
			return *this;
		}
		if (ptr->getRight() != NULL) 
		{
			ptr = T->Min(ptr->getRight());
			return *this;
		}
		Node<ValueType>* Current = ptr;

		while (true) {
			if (Current->getParent() == NULL)	return *this;

			if (Current->getParent()->getLeft() == Current) {
				ptr = Current->getParent();
				return *this;
			}
			Current = Current->getParent();
		}

	}

	TreeIterator& operator=(const TreeIterator& it) { T = it.T; ptr = it.ptr; return *this; }
	TreeIterator& operator=(Node<ValueType>* p) {
		if (p != NULL)
			ptr = p;
		return *this;
	}
private:
	Node<ValueType>* ptr;
	Tree<ValueType>* T;
};

template<class T>
class IteratedTree : public Tree<T>
{
public:
	IteratedTree<T>() : Tree<T>() {}

	TreeIterator<T> iterator;

	TreeIterator<T> begin() { TreeIterator<T> it = TreeIterator<T>(this, Tree<T>::Min()); return it; }
	TreeIterator<T> end() { TreeIterator<T> it = TreeIterator<T>(this, Tree<T>::Max()); return it; }
};

//AVL_Tree - потомок класса Tree
template<class T>
class AVL_Tree : public IteratedTree<T>
{
protected:
	//определение разности высот двух поддеревьев
	int bfactor(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	//краеугольные камни АВЛ-деревьев - процедуры поворотов
	Node<T>* RotateRight(Node<T>* p) // правый поворот вокруг p
	{
		Node<T>* q = p->getLeft();
		p->setLeft(q->getRight());
		q->setRight(p);
		if (p == Tree<T>::root)
			Tree<T>::root = q;

		q->setParent(p->getParent());
		p->setParent(q);
		if (p->getLeft() != NULL) p->getLeft()->setParent(p);

		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T>* RotateLeft(Node<T>* q) // левый поворот вокруг q
	{
		Node<T>* p = q->getRight();
		q->setRight(p->getLeft());
		p->setLeft(q);
		if (q == Tree<T>::root)
			Tree<T>::root = p;

		p->setParent(q->getParent());
		q->setParent(p);
		if (q->getRight() != NULL) q->getRight()->setParent(q);

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T>* Balance(Node<T>* p) // балансировка узла p
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->getRight()) < 0)
			{
				p->setRight(RotateRight(p->getRight()));
				p->getRight()->setParent(p);
			}
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->getLeft()) > 0)
			{
				p->setLeft(RotateLeft(p->getLeft()));
				p->getLeft()->setParent(p);
			}
			return RotateRight(p);
		}

		return p; // балансировка не нужна
	}

public:
	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree<T>() : IteratedTree<T>() {}

	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, Tree<T>::root);
	}

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		//вызываем функцию Add_R из базового класса
		Node<T>* AddedNode = Tree<T>::Add_R(N, Current);
		//применяем к добавленному узлу балансировку
		return Balance(AddedNode);
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* Add(T n)
	{
		Node<T>* N = new Node<T>(n);
		return Add_R(N);
	}

	//удаление узла
	virtual void Remove(Node<T>* N)
	{ }
};



int main()
{
	AVL_Tree<double> T;
	int arr[15];
	int i = 0;
	for (i = 0; i < 15; i++) arr[i] = (int)(100 * cos(15 * double(i + 1)));
	for (i = 0; i < 15; i++)
		T.Add(arr[i]);

	Node<double>* M = T.Min();
	cout << "\nMin = " << M->getData() << "\tFind " << arr[3] << ": " << T.Find_R(arr[3], T.getRoot());

	void (*f_ptr)(Node<double>*); f_ptr = print;
	/*cout << "\n-----\nPreorder:";
	T.PreOrder(T.getRoot(), f_ptr);*/
	cout << "\n-----\nInorder:";
	T.InOrder(T.getRoot(), f_ptr);
	/*cout << "\n-----\nPostorder:";
	T.PostOrder(T.getRoot(), f_ptr);*/
	cout << "\nIterators:\n";
	T.iterator = T.begin();
	while (T.iterator != T.end())
	{
		cout << *T.iterator << " ";
		T.iterator++;
	}
	cout << *T.iterator << " ";

	char c; cin >> c;
	return 0;
}
