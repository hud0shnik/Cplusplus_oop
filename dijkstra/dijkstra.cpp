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
		if (from < E.from)
			return true;
		if (from == E.from && to < E.to)
			return true;
		return false;
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


int main()
{
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
	}

	// Печать
	print_matrix(matrix);*/

	vector<vector<int> > mat =
	{
	{0, 3, 1, 3, 0, 0, 0},
	{3, 0, 0, 3, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0},
	{3, 3, 1, 0, 1, 0, 0},
	{0, 0, 0, 1, 0, 1, 2},
	{0, 0, 0, 0, 1, 0, 3},
	{0, 0, 0, 0, 2, 3, 0}
	};
	print_matrix(mat);

	//used[i] = 0 вершина еще не появлялась при обработке
	vector<int> used(7, 0);
	vector<int> dist(7, 10000);

	//BFS
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	int step = 0;

	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();

		for (int i = 6; i >=0; i--)
		{
			//есть ребро vertex->i, в i не заходили
			if (mat[vertex][i] > 0 && mat[vertex][i] < 10000 && dist[i] > dist[vertex] + mat[vertex][i])
			{
				q.push(i);
				//вершину видели, но не обработали
				used[i] = 1;

				dist[i] = dist[vertex] + mat[vertex][i];
			}
		}

		//обработка вершины закончена
		//if (dist[vertex] < 0) dist[vertex] = step;
		used[vertex] = 2;
		cout << "\nVertex " << vertex;
		step++;
	}

	cout << "\nVisited vertices: ";
	for (int i = 0; i < 7; i++) cout << used[i] << " ";
	cout << "\nDistances: ";
	for (int i = 0; i < 7; i++) cout << dist[i] << " ";
	char c1; cin >> c1;

	std::vector<std::vector<int> > mat1 =
	{
		{0, 1, 2, 3, 4, 5, 0},
		{1, 0, 0, 0, 0, 2, 0},
		{2, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 3, 0, 0},
		{4, 0, 0, 3, 0, 0, 0},
		{5, 2, 0, 0, 0, 0, 5},
		{0, 0, 0, 0, 0, 5, 0}
	};
	int mst_weight = 0;


	std::cout << "\nMinimum spanning tree weight: " << mst_weight << endl;

	mst_weight = 0;     //Текущий вес остова.
	//vector <int> used(7, 0); //использованные вершины
	for (int i = 0; i < 7; i++) used[i] = 0;
	vector<Edge> edges;		//рассматриваемые ребра
	vector<Edge> tree_edges;	//ребра в минимальном остове

	edges.push_back(Edge(0, 0, 0));     //Начнём с вершины 0.


	while (!edges.empty())
	{

	}

	std::cout << "\nMinimum spanning tree weight: " << mst_weight << endl;
	for (int i = 1; i < tree_edges.size(); i++)
	{
		cout << "\nEdge " << i << " ";
		cout << tree_edges[i];
	}

	char c; std::cin >> c;
	return 0;
}