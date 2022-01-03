#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 10000 // условное число, обозначающее бесконечность

void FillVectorWith(vector < int > & v, int value, int size = 0) {
  if (size != 0) {
    v.resize(0);
    for (int i = 0; i < size; i++)
      v.push_back(value);
  }
  for (int i = 0; i < v.size(); i++)
    v[i] = value;
}

void FillMatrixWith(vector < vector < int > > & matrix, int value, int width = 0, int height = 0) {
  if (width != 0 && height != 0) {
    matrix.resize(0);
    int i, j;
    for (i = 0; i < height; i++) {
      vector < int > v1;
      for (j = 0; j < width; j++) {
        v1.push_back(value);
      }
      matrix.push_back(v1);
    }
  }
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++)
      matrix[i][j] = value;
  }
}

int FindPath(vector < vector < int > > & f, vector < vector < int > > & c, int source, int target, int vertices) // source - исток, target - сток
{
  int i;
  int CurVertex;
  // Flow - значение потока через данную вершину на данном шаге поиска
  // Link[i] хранит номер предыдущей вешины на пути i -> исток
  vector < int > Flow;
  FillVectorWith(Flow, 0, vertices);
  vector < int > Link;
  FillVectorWith(Link, -1, vertices);
  Flow[source] = INF;

  priority_queue < int > q;
  q.push(source);

  while (!q.empty()) {
    CurVertex = q.top();
    q.pop();

    for (int i = 0; i < vertices; i++) {
      if (c[CurVertex][i] - f[CurVertex][i] > 0 && Flow[i] == 0) {
        q.push(i);

        Link[i] = CurVertex;

        if (c[CurVertex][i] - f[CurVertex][i] < Flow[CurVertex])
          Flow[i] = c[CurVertex][i] - f[CurVertex][i];
        else
          Flow[i] = Flow[CurVertex];
      }
    }
  }

  if (Link[target] == -1) return 0;

  cout << "\nFlow: " << Flow[target] << " Link: ";
  for (int i = 0; i < vertices; i++) cout << Link[i] << " ";

  CurVertex = target;
  while (CurVertex != source) {
    f[Link[CurVertex]][CurVertex] += Flow[target];
    CurVertex = Link[CurVertex];
  }
  return Flow[target];
}

// основная функция поиска максимального потока
int MaxFlow(vector < vector < int > > & f, vector < vector < int > > & c, int source, int target, int vertices) // source - исток, target - сток
{
  // f - flow matrix
  FillMatrixWith(f, 0);
  int MaxFlow = 0;
  int AddFlow;
  do {
    AddFlow = FindPath(f, c, source, target, vertices);
    MaxFlow += AddFlow;
  } while (AddFlow > 0);
  return MaxFlow;
}

int main() {
  int source = 0; //откуда
  int target = 5; //куда
  int vertices = 6; // число вершин в графе

  vector < vector < int >> a = {
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

  vector < vector < int > > f;
  // f[i][j] - поток, текущий от вершины i к j
  // c[i][j] - максимальная величина потока, способная течь по ребру (i,j)
  FillMatrixWith(f, 0, vertices, vertices);

  // набор вспомогательных переменных, используемых функцией FindPath - обхода в ширину

  // поиск пути, по которому возможно пустить поток алгоритмом обхода графа в ширину
  // функция ищет путь из истока в сток, по которому еще можно пустить поток,
  // считая вместимость ребера (i,j) равной c[i][j] - f[i][j]

  cout << "\nResult: " << MaxFlow(f, a, source, target, vertices);
  char c1;
  cin >> c1;
  return 0;
}