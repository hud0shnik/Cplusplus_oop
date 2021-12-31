using namespace std;
#include <map>
#include <iostream>

struct Film
{
	int Income;
	Film() { Income = rand() % 1000000; }
	friend std::ostream& operator<<(std::ostream& stream, const Film& Film)
	{
		stream << "Income:" << Film.Income<<"$";
		return stream;
	}
};

bool operator==(Film film1, Film film2)
{
	if (film1.Income == film2.Income)
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

bool Predicat(Film film)
{
	if (film.Income > 500000) return true;
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
	map<string, Film> Films;
	Film a, b, c, d, e, k;
	Films["Film A"] = a;
	Films["Film B"] = b;
	Films["Film C"] = c;
	Films["Film D"] = d;
	Films["Film E"] = e;
	Films["Film K"] = k;
	auto f = FindByKey<string, Film>(Films, "Film A");
	cout << "Key: " << f.first << ", value: " << f.second << endl;
	cout << endl;
	auto g = FindByValue<string, Film>(Films, d);
	cout << "Key: " << g.first << ", value: " << g.second << endl;
	cout << endl;
	Print(Films);
	cout << endl;
	auto h = filter(Films, Predicat);
	Print(h);
}