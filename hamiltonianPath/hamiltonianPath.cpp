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

bool hamilton(vector < vector < int > > & mat, vector < bool > & visited, vector < int > & path, int curr) {
  path.push_back(curr);
  //путь содержит все вершины: если есть связь последней вершины с исходной, цикл найден
  //если нет, откатываемся на шаг назад

  //вершина использована в пути
  visited[curr] = true;
  //проверить всех непосещенных соседей вершины curr

  //этот путь не подходит, убираем вершину и откатываемся
  visited[curr] = false;
  path.pop_back();
  return false;
}

int main() {
	
	vector<vector<int> > mat =
	{
	{ 0, 1, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 0, 0 },
	{ 0, 1, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 1, 0, 1 },
	{ 0, 0, 0, 0, 1, 0 }
	};
  vector < bool > visited(6, 0);
  vector < int > path;

  cout << "\nHamilton: " << hamilton(mat, visited, path, 0);

  char c1;
  cin >> c1;

  char c;
  std::cin >> c;
  return 0;
}