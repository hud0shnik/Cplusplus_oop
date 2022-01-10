#include <iostream>
#include <map>
#include <vector>

using namespace std;

string calculate(vector<pair<string, string>>v, string cm) {
    map<string, string> result;
    for (int i = 0; i < v.size(); i++) {
        result[v[i].first] += v[i].second + " ";
    }
    return result[cm];
}

string calculate_faster(vector<pair<string, string>>v, string cm) {
    string result;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].first == cm){
            result += v[i].second+ " ";
        }
    }
    return result;
}

int main(){
    vector<pair<string, string>> players;
    players.push_back(pair<string, string>{"Spartak", "Semen P"});
    players.push_back(pair<string, string>{"Spartak", "Vladimyr K"});
    players.push_back(pair<string, string>{"Krylya Sovetov", "Frolov E"});
    players.push_back(pair<string, string>{"Spartak", "Dmitry N"});
    players.push_back(pair<string, string>{"Krylya Sovetov", "Ovsyannikov B"});

    std::cout << "Spartak players:\t" << calculate(players, "Spartak")<<"\n";
    std::cout << "Krylya Sovetov players:\t" << calculate_faster(players, "Krylya Sovetov");

    return 0;
}
