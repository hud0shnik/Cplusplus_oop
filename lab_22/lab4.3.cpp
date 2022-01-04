#include <iostream>
#include <iomanip>  
#include <set>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


class Edge
{
public:
	int from, to, weight;
	Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
	Edge(const Edge& E)
	{
		from = E.from;
		to = E.to;
		weight = E.weight;
	}
	int operator<(Edge& E)
	{
		return (weight < E.weight);
	}
	friend ostream& operator<<(ostream& s, Edge& e);
};

ostream& operator<<(ostream& s, Edge& e)
{
	s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
	return s;
}
//для планарного графа достаточно 4х цветов, если граф не планарный то может понадобиться больше цветов
void paintgraph(vector<vector<int> >& matrix, vector <int>& color, int curr = 0)
{
	//структура данных для цветов смежных вершин с исследуемой
	set<int> neighbours;//set-потому что поиск и добавление идет максимально быстро
	//аналоги поиска в ширину
	queue<int> q;
	q.push(curr);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		//вершина уже закрашена?
		if (color[curr] != 0)
			continue;
		neighbours.clear();

		for (int next = 0; next < matrix.size(); next++)
			if (matrix[curr][next] == 1 && !color[next])
			{

				//проверяем цвета всех смежных вершин
				if (color[next])
				{
					neighbours.insert(color[next]);
				}
				else
				{
					q.push(next);
				}
			}

		//счетчик цветов - ищем допустимый цвет с наименьшим индексом
		int color_counter = 1;
		auto it = neighbours.begin();
		do
		{
			//есть ли этот номер цвета среди соседей?
			it = neighbours.find(color_counter);
			if (it == neighbours.end())
			{//цвет не найден- выходим
				break;
			}
			color_counter++;
		} while (true);

		//красим вершину в допустимый цвет
		color[curr] = color_counter;
	}
}

int main() {

	vector<vector<int> > mat =
	{
		{ 0, 7, 7, 9, 0, 4, 7, 6, 4, 4, 1, 4 },
		{ 7, 0, 7, 5, 5, 2, 1, 1, 8, 5, 9, 0 },
		{ 7, 7, 0, 8, 9, 0, 9, 8, 9, 7, 4, 1 },
		{ 9, 5, 8, 0, 7, 3, 9, 6, 5, 5, 5, 2 },
		{ 0, 5, 9, 7, 0, 9, 9, 3, 5, 9, 0, 2 },
		{ 4, 2, 0, 3, 9, 0, 3, 2, 3, 2, 9, 3 },
		{ 7, 1, 9, 9, 9, 3, 0, 2, 7, 2, 4, 7 },
		{ 6, 1, 8, 6, 3, 2, 2, 0, 3, 3, 6, 9 },
		{ 4, 8, 9, 5, 5, 3, 7, 3, 0, 5, 6, 2 },
		{ 4, 5, 7, 5, 9, 2, 2, 3, 5, 0, 6, 4 },
		{ 1, 9, 4, 5, 0, 9, 4, 6, 6, 6, 0, 7 },
		{ 4, 0, 1, 2, 2, 3, 7, 9, 2, 4, 7, 0 },
	};

	vector<int> color(12, 0);
	paintgraph(mat, color, 0);
	std::cout << "\nColor: ";
	for (int i = 0; i < 12; i++) std::cout << color[i] << " ";

	char c1; cin >> c1;

	return 0;
}
