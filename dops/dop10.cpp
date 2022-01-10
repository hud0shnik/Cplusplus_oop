#include <iostream>
#include <map>
#include <vector>
using namespace std;

map < int, int > calculate(vector < int > m) {
    map < int, int > result;
    for (int i = 0; i < m.size(); i++) {
        result[m[i]]++;
    }
    return result;
}

int main() {
    vector<int> m{ 2,3,4,5,5,5,5,1,0,0,1 };
    map < int, int > map;
    map = calculate(m);

    cout << "Map:\n";
    for (int i = 0; i < 6; i++) {
        cout << i << " : " << map[i] << "\n";
    }
    return 0;
}