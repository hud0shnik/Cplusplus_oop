using namespace std;
#include <map>
#include <iostream>

struct Locality
{
	int Population;
	Locality() { Population = rand() % 1000000; }
	friend std::ostream& operator<<(std::ostream& stream, const Locality& Locality)
	{
		stream << "Population:" << Locality.Population<<"$";
		return stream;
	}
};

bool operator==(Locality Locality1, Locality Locality2)
{
	if (Locality1.Population == Locality2.Population)
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
		cout << "Key: " << it_m->first << ", value: " << it_m->second << "\n";
		it_m++;
	}
}

bool Predicat(Locality Locality)
{
	if (Locality.Population > 500000) return true;
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
	map<string, Locality> Localitys;
	Locality a, b, c, d, e, k;
	Localitys["Locality A"] = a;
	Localitys["Locality B"] = b;
	Localitys["Locality C"] = c;
	Localitys["Locality D"] = d;
	Localitys["Locality E"] = e;
	Localitys["Locality K"] = k;
	auto f = FindByKey<string, Locality>(Localitys, "Locality A");
	cout << "Key: " << f.first << ", value: " << f.second << endl;
	cout << endl;
	auto g = FindByValue<string, Locality>(Localitys, d);
	cout << "Key: " << g.first << ", value: " << g.second << endl;
	cout << endl;
	Print(Localitys);
	cout << endl;
	auto h = filter(Localitys, Predicat);
	Print(h);
}