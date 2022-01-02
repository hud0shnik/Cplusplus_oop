#include <iostream>
#include <vector>
#include <queue>


class Node {
  public:
    int Number;
  std::vector < int > Nodes;

  bool WasPassed = false;
  int Distance = 0;

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
  if (n1.Number > n2.Number)
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

/// Алгоритм Дейкстры
std::vector < Node > Deikstra(int index, std::vector < Node > nodes) {
  /// Очередь с приоритетом для всех элементов
  std::queue < Node > NodesQueue;

  std::vector < Node > ReturnVector = nodes;

  nodes[index].WasPassed = true;
  NodesQueue.push(nodes[index]);

  // Проход по очереди
  while (!NodesQueue.empty()) {
    for (int i = 0; i < nodes.size(); i++) {
      if (NodesQueue.front().Nodes[i] > 0 && NodesQueue.front().Distance + NodesQueue.front().Nodes[i] < nodes[i].Distance + NodesQueue.front().Nodes[i])
        nodes[i].WasPassed = false;

      if (NodesQueue.front().Nodes[i] > 0 && nodes[i].WasPassed == false) {
        nodes[i].WasPassed = true;
        nodes[i].Distance = NodesQueue.front().Distance + NodesQueue.front().Nodes[i];
        NodesQueue.push(nodes[i]);
      }
    }

    if (ReturnVector[NodesQueue.front().Number].Distance == 0)
      ReturnVector[NodesQueue.front().Number].Distance = NodesQueue.front().Distance;

    if (NodesQueue.front().Distance < ReturnVector[NodesQueue.front().Number].Distance && NodesQueue.front().Distance > 0)
      ReturnVector[NodesQueue.front().Number].Distance = NodesQueue.front().Distance;

    NodesQueue.pop();
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

  auto f = Deikstra(0, Nodes);

  std::cout << std::endl;

  for (int i = 0; i < f.size(); i++) {
    std::cout << "Number: " << f[i].Number << " Path length: " << f[i].Distance << std::endl;

    for (int j = 0; j < f[i].Nodes.size(); j++) {
      std::cout << f[i].Nodes[j] << " ";
    }
    std::cout << std::endl;
  }

}