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

bool hamilton(vector < vector < int > > & mat, vector < bool > & visited, vector < int > & path, int curr, bool flag = true) {
  path.push_back(curr);
  if (path.size() == mat.size()) {

    bool bl = flag ? true : (mat[curr][path[0]] > 0) ? true : false;
    if (bl)
      return bl;
  }
  visited[curr] = true;
  for (int i = 0; i < mat.size(); i++) {
    if (mat[curr][i] > 0 && !visited[i]) {
      if (hamilton(mat, visited, path, i, flag)) {
        return true;
      }
    }
  }
  visited[curr] = false;
  path.pop_back();
  return false;
}

vector < int > hamilton(vector < vector < int > > & mat, vector < bool > & visited, int curr, bool flag = true) {
  vector < int > path;
  path.push_back(curr);
  if (path.size() == mat.size()) {

    bool re = flag ? true : (mat[curr][path[0]] > 0) ? true : false;
    if (re)
      return path;
  }
  visited[curr] = true;
  for (int i = 0; i < mat.size(); i++) {
    if (mat[curr][i] > 0 && !visited[i]) {
      if (hamilton(mat, visited, path, i, flag)) {
        return path;
      }
    }
  }
  path.clear();
  path.push_back(curr);
  return path;
}

int main() {

  vector < vector < int > > mat = {
    {
    { 0, 9, 5, 4, 8, 5, 1, 6, 1, 9, 5, 0 },
    { 9, 0, 1, 7, 7, 8, 2, 8, 2, 0, 7, 3 },
    { 5, 1, 0, 4, 0, 9, 4, 4, 5, 2, 3, 1 },
    { 4, 7, 4, 0, 5, 3, 8, 2, 3, 4, 5, 9 },
    { 8, 7, 0, 5, 0, 5, 4, 7, 7, 5, 4, 4 },
    { 5, 8, 9, 3, 5, 0, 5, 9, 4, 8, 1, 1 },
    { 1, 2, 4, 8, 4, 5, 0, 1, 6, 4, 2, 0 },
    { 6, 8, 4, 2, 7, 9, 1, 0, 8, 9, 4, 4 },
    { 1, 2, 5, 3, 7, 4, 6, 8, 0, 2, 0, 7 },
    { 9, 0, 2, 4, 5, 8, 4, 9, 2, 0, 3, 4 },
    { 5, 7, 3, 5, 4, 1, 2, 4, 0, 3, 0, 2 },
    { 0, 3, 1, 9, 4, 1, 0, 4, 7, 4, 2, 0 },
	}
  };
  vector < bool > visited(mat.size(), 0);
  vector < int > path = hamilton(mat, visited, 0, false);
  for (auto gg: path) {
    cout << gg << '\n';
  }
  return 0;
}