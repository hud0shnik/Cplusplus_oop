#include <iostream>
#include <vector>
#include <queue>

class Node {
  public:
    int Number;
  std::vector < int > Nodes;

  int DistanceToThisElement = 0;
  int SourceElement;
  bool WasPassed = false;
  bool WasFinallyPassed = false;

  Node(int number, std::vector < int > nodes): Number(number), Nodes(nodes) {}

  friend bool operator < (const Node & n1,
    const Node & n2);

  bool operator == (const Node & n) {
    if (Number == n.Number)
      return true;
    return false;
  }

  friend std::ostream & operator << (std::ostream & stream, Node & nod);
};

std::ostream & operator << (std::ostream & str,
  const Node & nod) {
  str << "Number: " << nod.Number;
  return str;
}

bool operator < (const Node & n1,
  const Node & n2) {
  if (n1.DistanceToThisElement > n2.DistanceToThisElement)
    return true;
  return false;
}

template < class T >
  void PrinPriorityQueue(std::priority_queue < T > q) {
    while (!q.empty()) {
      std::cout << q.top() << std::endl;
      q.pop();
    }
  }

// Алгоритм Прима
std::vector < Node > FindOstov(int index, std::vector < Node > nodes) {
  // Очередь с приоритетом для всех элементов
  std::priority_queue < Node > NodesQueue;

  std::vector < Node > ReturnVector;
  ReturnVector.reserve(nodes.size());

  // Добавляем в очередь первый элемент
  nodes[index].SourceElement = index;
  nodes[index].WasPassed = true;
  //nodes[index].WasFinallyPassed = true;
  NodesQueue.push(nodes[index]);

  // Проход по очереди
  while (!NodesQueue.empty()) {
    // Сохраняем первый элемент из очереди для получения значений, а затем удаляем его из очереди
    auto f = NodesQueue.top();
    NodesQueue.pop();

    // В этом цикле мы проходим по всему вектору вершин. 
    // Тут мы определяем дистанцию от текущего элемента в очереди до каждого элемента вектора
    // Помечаем вершину пройденной с помощью массива пройденных вершин
    for (int i = 0; i < nodes.size(); i++) {
      // Если мы были в вершине, но она не была напечатана и расстояние до нее от текущей вершины из очереди меньше, то мы должны повторно добавить ее в очередь
      if (nodes[i].WasPassed == true && nodes[i].WasFinallyPassed == false && f.Nodes[i] < nodes[i].DistanceToThisElement && nodes[i].DistanceToThisElement > 0)
        nodes[i].WasPassed = false;

      // Установка источника и расстояния для текущего элемента
      nodes[i].SourceElement = f.Number;
      nodes[i].DistanceToThisElement = f.Nodes[i];

      // Если мы не были в этой вершине и расстояние до нее больше ноля, то мы заходим в нее
      if (nodes[i].WasPassed == false && nodes[i].WasFinallyPassed == false && nodes[i].Nodes[f.Number] > 0) {
        nodes[i].WasPassed = true;
        NodesQueue.push(nodes[i]);
      }
    }

    // Вывод элемента в консоль
    if (nodes[f.Number].WasFinallyPassed == false) {
      //std::cout << "From: " << f.SourceElement << " With distance: " << nodes[f.SourceElement].Nodes[f.Number] << " To: " << f.Number << std::endl;
      ReturnVector.push_back(f);
    }
    // Говорим что прошли вершину окончательно
    nodes[f.Number].WasFinallyPassed = true;
  }

  return ReturnVector;
}

int main() {
  std::vector < std::vector < int >> Matrix = {
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

  std::vector < Node > Nodes;
  for (int i = 0; i < Matrix.size(); i++)
    Nodes.push_back(Node(i, Matrix[i]));

  auto f = FindOstov(0, Nodes);

  for (int i = 0; i < f.size(); i++) {
    std::cout << " From: " << f[i].SourceElement << " With distance: " << f[i].Nodes[f[i].SourceElement] << " To: " << f[i].Number << " Paths: ";

    for (int j = 0; j < f[i].Nodes.size(); j++) {
      std::cout << f[i].Nodes[j] << " ";
    }
    std::cout << std::endl;
  }
}