#include <iostream>
#include <list>
#include <complex>
#include <cmath>
// Интелектуальна собственность самого Меня!!!(Дани)
using namespace std;


void push(list<complex<int>> &lst, complex<int> element)
{
	auto it = lst.begin();
	// real(element)* real(element) + imag(element)* imag(element) = |element|
	while ((it != lst.end()) && (sqrt(real(element) * real(element) + imag(element) * imag(element)) > sqrt(real(*it) * real(*it) + imag(*it) * imag(*it))))
	{
		*it++;
	}

	if (it != lst.end())
		lst.insert(it, element);
	else
		lst.push_back(element);
}
/*															Попытка сделать поп не увенчалась успехом
void pop(list<complex<int>>& lst, complex<int> element)
{
	auto it = lst.begin();
	auto it2 = lst.end();
	while ((it != lst.end()) && (sqrt(real(element) * real(element) + imag(element) * imag(element)) > sqrt(real(*it) * real(*it) + imag(*it) * imag(*it))))
	{
		*it++;
	}
	if (it != lst.end())
		//lst.insert(it, element);
		lst.erase(*it, );
	else
		lst.push_back(element);
}
*/
list<complex<int>> filter(list<complex<int>> Source, bool(*p)(complex<int>))
{
	list<complex<int>> result;
	list<complex<int>>::iterator it = Source.begin();
	while (it != Source.end()) {
		if (p(*it)) {
			result.push_back(*it);
		}
		*it++;
	}
	return result;
}

bool filtration(complex<int> a) {
	if (real(a) < 0) {
		return true;
	}
	return false;
}

int main() {
	list<complex<int>> lst, lst2;
	for (int i = 0; i < 10; i += 2) {
		std::complex<double> compNum(i, 1);
		lst.push_back(compNum);
	}
	push(lst, -5);
	push(lst, -3);
	push(lst, -10);
	//pop(lst, -5);
	list<complex<int>>::iterator it = lst.begin();
	while (it != lst.end()) {
		std::cout << *it << " ";
		*it++;
	}
	bool (*ptr)(complex<int>); ptr = filtration;
	lst2 = filter(lst, ptr);
	it = lst2.begin();
	cout << "\n";
	
	it = lst2.begin();
	while (it != lst2.end())
	{
		std::cout << *it << " ";
		*it++;
	}
	cout  << endl;
	
}