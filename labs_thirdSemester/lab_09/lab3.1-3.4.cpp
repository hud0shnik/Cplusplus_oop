#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

std::vector < int > bfs(const vector < vector < int > >& mat, const int index = 0) {
    queue < int > Queue;
    vector < int > used(mat.size(), 0);
    Queue.push(index);
    used[index] = 1;
    vector < int > dist(mat.size(), 10000);
    dist[index] = 0;
    while (!Queue.empty()) {
        int node = Queue.front();
        Queue.pop();
        if (used[node] == 2) continue;
        used[node] = 2;
        for (int j = 0; j < mat.size(); j++) { // проверяем для нее все смежные вершины
            if (mat[node][j] > 0) { // если вершина смежная и не обнаружена
                if (used[j] != 2) {
                    Queue.push(j); // добавляем ее в очередь
                    used[j] = 1; // отмечаем вершину как обнаруженную
                }
                if (dist[j] > dist[node] + mat[node][j]) {
                    dist[j] = dist[node] + mat[node][j];
                    if (used[j] != 1) {
                        Queue.push(j);
                        used[j] = 1;
                    }
                }
            }
        }
    }

    return dist;
}

vector < int > powers(const vector < vector < int > >& mat) {
    queue < int > Queue;
    vector < int > used(mat.size(), 0);
    //BFS – поиск в ширину
    Queue.push(0); //в качестве начальной вершины используем 0.
    used[0] = 1;
    vector < int > power(mat.size(), 0); //расстояния до вершин от 0-й в числе ребер
    double summp = 0;
    while (!Queue.empty()) {
        int node = Queue.front(); //извлекаем из очереди текущую вершину
        Queue.pop();
        //Здесь должна быть обработка текущей вершины.
        if (used[node] == 2) continue;
        used[node] = 2;
        for (int j = 0; j < mat.size(); j++) { // проверяем для нее все смежные вершины
            if (mat[node][j] > 0) { // если вершина смежная и не обнаружена
                if (used[j] != 2) {
                    Queue.push(j); // добавляем ее в очередь
                    used[j] = 1; // отмечаем вершину как обнаруженную
                }
                power[node]++;
            }
        }
        summp += power[node];
    }

    cout << "\nAverage powers of graph: " << (summp / mat.size());

    return power;
}

vector < vector < int > > osto_tree(const vector < vector < int > > mat) {
    int u, v, gran_cnt = 1;
    vector < int > visited(mat.size(), 0), path(mat.size() * mat.size());
    vector < vector < int > > cost(mat);

    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat.size(); j++) {
            if (cost[i][j] == 0) cost[i][j] = 10000;
        }
    visited[0] = 1;

    while (gran_cnt < mat.size()) {
        for (int i = 0, min = 10000; i < mat.size(); i++)
            for (int j = 0; j < mat.size(); j++)
                if (cost[i][j] < min)
                    if (visited[i] != 0) {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
        if (visited[u] == 0 || visited[v] == 0) {
            path[gran_cnt - 1] = v;
            gran_cnt++;
            visited[v] = 1;

        }
        cost[u][v] = cost[v][u] = 10000;
    }

    vector < vector < int > > result(mat.size(), vector < int >(mat.size(), 0));
    for (int i = 0; i < mat.size() - 1; i++) {
        int prev = ((i > 0) ? path[i - 1] : 0);
        int cur = path[i];
        if (mat[prev][cur] > 0) {
            result[prev][cur] = mat[prev][cur];
            result[cur][prev] = mat[cur][prev];
        }
        else
            for (int j = i; j-- > 0;) {
                int prev_prev = path[j];
                if (mat[prev_prev][cur] > 0) {
                    result[prev_prev][cur] = mat[prev_prev][cur];
                    result[cur][prev_prev] = mat[cur][prev_prev];
                    break;
                }
            }
    }

    return result;
}

void printDfs(const vector < vector < int > > mat) {
    vector < int > used(mat.size(), 0);
    //0 – вершина не посещена при поиске, 1 – помещена в структуру данных для вершин,
    //но не обработана, 2 – обработана, смежные вершины помещены в структуру данных
    //DFS – поиск в глубину
    stack < int > Stack;
    Stack.push(0); // помещаем в очередь первую вершину
    while (!Stack.empty()) { // пока стек не пуст
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();
        cout << node << " | ";
        if (used[node] == 2) continue;
        used[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < mat.size(); j++) { // проверяем для нее все смежные вершины
            if (mat[node][j] > 0 && used[j] != 2) { // если вершина смежная и не обнаружена
                Stack.push(j); // добавляем ее в cтек
                used[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
    }
    cout << '\n';
}

int main() {
    // матрица смежности
    vector < vector < int > > mat = {
      {
        { 0, 9, 7, 1, 5, 4, 5, 3, 8, 1, 0, 7, 4, 0, 8 },
        { 9, 0, 7, 3, 2, 7, 0, 9, 8, 5, 0, 6, 4, 1, 3 },
        { 7, 7, 0, 2, 2, 2, 2, 3, 9, 5, 1, 5, 0, 4, 4 },
        { 1, 3, 2, 0, 4, 4, 1, 0, 6, 9, 7, 2, 3, 6, 2 },
        { 5, 2, 2, 4, 0, 4, 4, 8, 4, 2, 4, 5, 7, 6, 9 },
        { 4, 7, 2, 4, 4, 0, 9, 0, 3, 1, 6, 4, 8, 8, 8 },
        { 5, 0, 2, 1, 4, 9, 0, 2, 2, 4, 5, 4, 2, 6, 1 },
        { 3, 9, 3, 0, 8, 0, 2, 0, 4, 1, 9, 9, 5, 5, 7 },
        { 8, 8, 9, 6, 4, 3, 2, 4, 0, 0, 7, 3, 7, 4, 1 },
        { 1, 5, 5, 9, 2, 1, 4, 1, 0, 0, 7, 6, 1, 2, 9 },
        { 0, 0, 1, 7, 4, 6, 5, 9, 7, 7, 0, 9, 6, 7, 8 },
        { 7, 6, 5, 2, 5, 4, 4, 9, 3, 6, 9, 0, 6, 2, 2 },
        { 4, 4, 0, 3, 7, 8, 2, 5, 7, 1, 6, 6, 0, 2, 7 },
        { 0, 1, 4, 6, 6, 8, 6, 5, 4, 2, 7, 2, 2, 0, 7 },
        { 8, 3, 4, 2, 9, 8, 1, 7, 1, 9, 8, 2, 7, 7, 0 }
      }
    }; 

    vector < vector < int > > osto_mat = osto_tree(mat);
    cout << "\nOsto tree matrix: \n";
    for (int i = 0; i < osto_mat.size(); i++) {
        for (int j = 0; j < osto_mat[i].size(); j++)
            cout << osto_mat[i][j] << ' ';
        cout << '\n';
    }
    vector < int > Powers = powers(mat);
    cout << "\nPowers ";
    for (int i = 0; i < mat.size(); i++) cout << Powers[i] << " ";

    vector < int > dist = bfs(mat, 0);
    cout << "\nDistances ";
    for (int i = 0; i < mat.size(); i++) cout << dist[i] << " ";

    cout << "\nOsto tree dfs: \n";
    printDfs(osto_mat);

}