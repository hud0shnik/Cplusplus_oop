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
        { 8, 3, 4, 2, 9, 8, 1, 7, 1, 9, 8, 2, 7, 7, 0 },
	}
  };
  vector < bool > visited(mat.size(), 0);
  vector < int > path = hamilton(mat, visited, 0, false);
  for (auto gg: path) {
    cout << gg << '\n';
  }
  return 0;
}