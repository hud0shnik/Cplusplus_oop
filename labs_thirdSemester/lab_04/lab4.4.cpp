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
	{ 0, 8, 2, 0, 5, 1, 7, 3, 5, 9, 3, 7 },
	{ 8, 0, 7, 5, 7, 1, 9, 1, 1, 6, 6, 9 },
	{ 2, 7, 0, 9, 3, 5, 1, 9, 1, 0, 8, 0 },
	{ 0, 5, 9, 0, 8, 8, 4, 0, 3, 5, 7, 8 },
	{ 5, 7, 3, 8, 0, 1, 7, 3, 0, 6, 8, 9 },
	{ 1, 1, 5, 8, 1, 0, 7, 0, 0, 8, 6, 9 },
	{ 7, 9, 1, 4, 7, 7, 0, 0, 7, 2, 5, 8 },
	{ 3, 1, 9, 0, 3, 0, 0, 0, 1, 8, 8, 1 },
	{ 5, 1, 1, 3, 0, 0, 7, 1, 0, 8, 6, 9 },
	{ 9, 6, 0, 5, 6, 8, 2, 8, 8, 0, 2, 7 },
	{ 3, 6, 8, 7, 8, 6, 5, 8, 6, 2, 0, 4 },
	{ 7, 9, 0, 8, 9, 9, 8, 1, 9, 7, 4, 0 },
	}
  };
  vector < bool > visited(mat.size(), 0);
  vector < int > path = hamilton(mat, visited, 0, false);
  for (auto gg: path) {
    cout << gg << '\n';
  }
  return 0;
}