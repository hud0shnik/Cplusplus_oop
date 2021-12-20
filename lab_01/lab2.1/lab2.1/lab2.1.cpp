using namespace std;
#include <map>
#include <iostream>

struct Home
{
	int Price;
	Home() { Price = rand() % 1000000; }
	friend std::ostream& operator<<(std::ostream& stream, const Home& Home)
	{
		stream << "Price:" << Home.Price<<"$";
		return stream;
	}
};

bool operator==(Home Home1, Home Home2)
{
	if (Home1.Price == Home2.Price)
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

bool Predicat(Home Home)
{
	if (Home.Price > 500000) return true;
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
	map<string, Home> Homes;
	Home a, b, c, d, e;
	Homes["Home A"] = a;
	Homes["Home B"] = b;
	Homes["Home C"] = c;
	Homes["Home D"] = d;
	Homes["Home E"] = e;
	auto f = FindByKey<string, Home>(Homes, "Home A");
	cout << f.first << " : " << f.second << endl;
	cout << endl;
	auto g = FindByValue<string, Home>(Homes, d);
	cout << g.first << " : " << g.second << endl;
	cout << endl;
	Print(Homes);
	cout << endl;
	auto h = filter(Homes, Predicat);
	Print(h);
}