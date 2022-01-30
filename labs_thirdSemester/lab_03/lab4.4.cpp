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
      { 0, 1, 7, 0, 9, 2, 4, 9, 3, 1, 4, 7, 3 },
      { 1, 0, 8, 6, 0, 0, 4, 8, 5, 7, 6, 7, 4 },
      { 7, 8, 0, 9, 6, 0, 6, 1, 3, 0, 4, 4, 9 },
      { 0, 6, 9, 0, 4, 5, 1, 1, 5, 6, 4, 9, 3 },
      { 9, 0, 6, 4, 0, 7, 0, 0, 9, 0, 4, 7, 6 },
      { 2, 0, 0, 5, 7, 0, 4, 5, 3, 8, 5, 1, 8 },
      { 4, 4, 6, 1, 0, 4, 0, 3, 4, 3, 4, 8, 0 },
      { 9, 8, 1, 1, 0, 5, 3, 0, 3, 5, 7, 5, 6 },
      { 3, 5, 3, 5, 9, 3, 4, 3, 0, 2, 3, 0, 4 },
      { 1, 7, 0, 6, 0, 8, 3, 5, 2, 0, 7, 9, 4 },
      { 4, 6, 4, 4, 4, 5, 4, 7, 3, 7, 0, 9, 8 },
      { 7, 7, 4, 9, 7, 1, 8, 5, 0, 9, 9, 0, 6 },
      { 3, 4, 9, 3, 6, 8, 0, 6, 4, 4, 8, 6, 0 },
	  }
  };
  
  vector < bool > visited(mat.size(), 0);
  vector < int > path = hamilton(mat, visited, 0, false);
  for (auto gg: path) {
    cout << gg << '\n';
  }
  return 0;
}