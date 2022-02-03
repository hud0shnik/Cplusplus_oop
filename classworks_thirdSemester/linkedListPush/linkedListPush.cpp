#include "stdafx.h"
using namespace std;
#include<list>
#include<iostream>

template<class T>
void push(list<T>& lst, T element)
{
	list<T>::iterator it = lst.begin();
	while(it!=lst.end() && *it < element)
		*it++;
	if(it!=lst.end())
		lst.insert(it, element);
	else 
		lst.push_back(element);
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	list<char> lst;
	for(int i=0;i<10;i+=2)
		lst.push_back(i);

	push(5); 

	list<char>::iterator it = lst.begin();
	while(it!=lst.end())
	{

		cout<<*it<<" ";
		*it++;
	}

	char c; cin>>c;
	return 0;
}

