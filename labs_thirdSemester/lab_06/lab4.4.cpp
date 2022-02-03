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
	  { 0, 5, 6, 6, 6, 4, 5, 0, 0, 8, 8, 4, 4 },
    { 5, 0, 8, 0, 3, 8, 4, 8, 6, 6, 6, 3, 4 },
    { 6, 8, 0, 2, 0, 0, 0, 9, 3, 5, 3, 8, 1 },
    { 6, 0, 2, 0, 2, 4, 7, 7, 7, 9, 5, 5, 5 },
    { 6, 3, 0, 2, 0, 1, 5, 5, 4, 4, 1, 4, 2 },
    { 4, 8, 0, 4, 1, 0, 8, 1, 5, 4, 5, 8, 6 },
    { 5, 4, 0, 7, 5, 8, 0, 6, 9, 0, 1, 2, 0 },
    { 0, 8, 9, 7, 5, 1, 6, 0, 4, 6, 7, 3, 3 },
    { 0, 6, 3, 7, 4, 5, 9, 4, 0, 4, 4, 1, 1 },
    { 8, 6, 5, 9, 4, 4, 0, 6, 4, 0, 9, 2, 7 },
    { 8, 6, 3, 5, 1, 5, 1, 7, 4, 9, 0, 6, 9 },
    { 4, 3, 8, 5, 4, 8, 2, 3, 1, 2, 6, 0, 3 },
    { 4, 4, 1, 5, 2, 6, 0, 3, 1, 7, 9, 3, 0 },
	  }
  };
  
  vector < bool > visited(mat.size(), 0);
  vector < int > path = hamilton(mat, visited, 0, false);
  for (auto gg: path) {
    cout << gg << '\n';
  }
  return 0;
}