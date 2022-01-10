#include <iostream>
#include <set>
#include <vector>
using namespace std;

vector <int> calculate(vector < int > m) {
    vector < int> result;
    set <int> st;
    

    for (int i = 0; i < m.size(); i++) {
        st.insert(m[i]);
    }
    set <int> ::iterator it = st.begin();
    for (int i = 1; it != st.end(); i++, it++) {
        result.push_back(*it);
    }

    return result;
}

int main() {
    vector<int> m{ 2,3,4,5,5,5,5,1,0,0,1 }, m1;

    cout << "Vector0:\t";
    for (int i : m){
        cout << i<<" ";
    }

    m1 = calculate(m);
    cout << "\nVector1:\t";
    for (int i : m1) {
        cout << i << " ";
    }
   
    return 0;
}