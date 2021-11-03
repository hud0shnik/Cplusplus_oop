#include <iostream>
#include <iomanip>  
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <stack>
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

void print_matrix(vector<std::vector<int> >& matrix) {
	std::for_each(matrix.begin(), matrix.end(), [](std::vector<int>& ivec)
		{
			std::for_each(ivec.begin(), ivec.end(), [](int i)
				{
					std::cout << std::left << std::setw(5) << i;
				});
			std::cout << std::endl;
		});
}

bool try_kuhn(int v, vector < vector<int> >& g, vector<int>& used, vector<int>& mt) {
	if (used[v])  return false;
	//cout << "\nKuhn: " << v;
	for (int i = 0; i < mt.size(); ++i) cout << " mt[" << i << "] = " << mt[i];
	used[v] = true;
	for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		//либо вершина - часть текущего паросочетания, либо запускаем поиск нового решения, начинаюшегося с неё
		if (mt[to] == -1 || try_kuhn(mt[to], g, used, mt)) 
		{
			//cout << "\nto(" << to << ") = " << v;
			mt[to] = v;
			return true;
		}
	}
	return false;
}


int main() {

	/*std::vector<std::vector<int> > imatrix;
	const size_t row = 5;
	const size_t col = 3;
	// Заполнение
	for (size_t i = 0; i < row; ++i)
	{
		std::vector<int> temp;
		for (size_t j = 0; j < col; ++j)
			temp.push_back(rand() % 666);
		imatrix.push_back(temp);
	}

	print_matrix(imatrix);


	const size_t v_count = 5;
	std::vector<std::vector<int> > matrix(v_count, std::vector<int>(v_count, 0)); // квадратная матрица, инициализируем элементы первого вектора векторами с 0 элементами
	for (size_t i = 0; i < v_count; ++i)
	{
		for (size_t j = 0; j < v_count; ++j)
			matrix[i][j] = rand() % 2;
	}*/

	// Печать
	//print_matrix(matrix);



	// Алгоритм обхода в глубину DFS

	vector<vector<int> > mat =
	{
	{ 0, 1, 1, 0, 0, 0, 1, 0, 0, 0 }, // матрица смежности
	{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0  },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 1, 0, 0, 1, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
	};
	print_matrix(mat);

	//used[i] = 0 вершина еще не появлялась при обработке
	vector<int> used(10, 0);
	vector<int> dist(10, -1);

	//BFS
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	int step = 0;

	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();

		for (int i = 0; i < 10; i++)
		{
			//есть ребро vertex->i, в i не заходили
			if (mat[vertex][i] > 0 && used[i] < 2)
			{
				q.push(i);
				//вершину видели, но не обработали
				used[i] = 1;

				if (dist[i] < 0) dist[i] = dist[vertex] + 1;
			}
		}

		//обработка вершины закончена
		//if (dist[vertex] < 0) dist[vertex] = step;
		used[vertex] = 2;
		step++;
	}

	std::cout << "\nBFS Visited vertices ";
	for (int i = 0; i < 10; i++) std::cout << used[i] << " ";
	std::cout << "\nBFS Distances ";
	for (int i = 0; i < 10; i++) std::cout << dist[i] << " ";

	//DFS
	stack<int> s;
	s.push(0);
	for (int i = 0; i < 10; i++) {used[i] = 0;  dist[i] = -1;}
	dist[0] = 0;
	step = 0;

	while (!s.empty())
	{
		int vertex = s.top();
		s.pop();

		for (int i = 9; i >=0; i--)
		{
			//есть ребро vertex->i, в i не заходили
			if (mat[vertex][i] > 0 && used[i] < 2)
			{
				s.push(i);
				//вершину видели, но не обработали
				used[i] = 1;

				//if (dist[i] < 0) dist[i] = dist[vertex] + 1;
			}
		}

		//обработка вершины закончена
		if (dist[vertex] < 0) dist[vertex] = step;
		used[vertex] = 2;
		step++;
	}

	
	
	
	std::cout << "\nDFS Visited vertices ";
	for (int i = 0; i < 10; i++) std::cout << used[i] << " ";
	std::cout << "\nDFS Distances ";
	for (int i = 0; i < 10; i++) std::cout << dist[i] << " ";



	return 0;
}