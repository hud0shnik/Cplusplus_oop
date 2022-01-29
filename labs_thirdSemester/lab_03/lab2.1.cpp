using namespace std;
#include <map>
#include <iostream>

struct SmartPhone
{
	int Price;
	SmartPhone() { Price = rand() % 10000; }
	friend std::ostream& operator<<(std::ostream& stream, const SmartPhone& SmartPhone)
	{
		stream << "Price:" << SmartPhone.Price << "$";
		return stream;
	}
};

bool operator==(SmartPhone SmartPhone1, SmartPhone SmartPhone2)
{
	if (SmartPhone1.Price == SmartPhone2.Price)
		return true;
	else
		return false;
}

template <class TKey, class TValue>
pair<TKey, TValue> FindByKey(const map<TKey, TValue>& Map, TKey key)
{
	auto res = Map.find(key);

	if (res != Map.end())
	{
		return pair<TKey, TValue>(res->first, res->second);
	}
	return pair<TKey, TValue>(Map.end()->first, Map.end()->second);

}

template <class TKey, class TValue>
pair<TKey, TValue> FindByValue(const map<TKey, TValue>& Map, TValue value)
{
	auto it = Map.begin();
	while (it != Map.end())
	{
		if (it->second == value)
			return pair<TKey, TValue>(it->first, it->second);
		it++;
	}
	return pair<TKey, TValue>(Map.end()->first, Map.end()->second);
}

template <class TKey, class TValue>
void Print(const map<TKey, TValue>& Map)
{
	auto it_m = Map.begin();
	while (it_m != Map.end())
	{
		cout << it_m->first << " : " << it_m->second << "\n";
		it_m++;
	}
}

bool Predicat(SmartPhone SmartPhone)
{
	if (SmartPhone.Price > 5000) return true;
	return false;
}

template <class TKey, class TValue>
std::map<TKey, TValue> filter(std::map<TKey, TValue>& map, bool(*func)(TValue x))
{
	std::map<TKey, TValue> map2;
	for (auto element : map)
	{
		if (func(element.second)) { map2[element.first] = element.second; }
	}
	return map2;
}

int main()
{
	map<string, SmartPhone> SmartPhones;
	SmartPhone a, b, c, d, e;
	SmartPhones["SmartPhone A"] = a;
	SmartPhones["SmartPhone B"] = b;
	SmartPhones["SmartPhone C"] = c;
	SmartPhones["SmartPhone D"] = d;
	SmartPhones["SmartPhone E"] = e;
	auto f = FindByKey<string, SmartPhone>(SmartPhones, "SmartPhone A");
	cout << f.first << " : " << f.second << endl;
	cout << endl;
	auto g = FindByValue<string, SmartPhone>(SmartPhones, d);
	cout << g.first << " : " << g.second << endl;
	cout << endl;
	Print(SmartPhones);
	cout << endl;
	auto h = filter(SmartPhones, Predicat);
	Print(h);
}