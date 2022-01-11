#include <iostream>
#include <vector>
#include <list>
#include <set>
using namespace std;

list < string > calculate(vector < pair < string, string >> v) {
    //На вход функция получает вектор пар "Исполнитель - Альбом
    //Set нужен чтобы не выводить повторы, а в list будут записаны альбомы
    set < string > sett;
    list < string > lst;
    //Запись в set всех альбомов
    for (int i = 0; i < v.size(); i++) {
        sett.insert(v[i].second);
    }
    //Запись альбомов в list (так как в задании написано вывести "список")
    set < string > ::iterator it = sett.begin();
    for (int i = 1; it != sett.end(); i++, it++) {
        lst.push_back(*it);
    }
    return lst;
}

string calculate2(vector < pair < string, string >> v) {
    //Эта функция будет быстрее так как возвращает одну строку со всеми альбомами
    set < string > sett;
    string result;
    //Также запись в set
    for (int i = 0; i < v.size(); i++) {
        sett.insert(v[i].second);
    }
    set < string > ::iterator it = sett.begin();
    //Запись альбомов в string
    for (int i = 1; it != sett.end(); i++, it++) {
        result += *it + " ";
    }
    return result;
}
string calculate3(vector < pair < string, string >> v) {
    set < string > sett;
    string result;
    //Эта функция проходит по вектору один раз
    for (int i = 0; i < v.size(); i++) {
        //Если такого альбома нет в sett, добавляем его в result
        if (sett.find(v[i].second) == sett.end()) {
            result += v[i].second + " ";
            //И добовляем его в sett чтобы избежать повторений
            sett.insert(v[i].second);
        }
    }
    return result;
}

int main() {
    vector<pair<string, string>> players;
    players.push_back(pair<string, string>{"M1", "Album2"});
    players.push_back(pair<string, string>{"M2", "Album3"});
    players.push_back(pair<string, string>{"M3", "Album2"});
    players.push_back(pair<string, string>{"M1", "Album0"});
    players.push_back(pair<string, string>{"M3", "Album1"});

    list<string> albums = calculate(players);
    std::cout << "Albums: \n";

    list <string> ::iterator it = albums.begin();
    for (int i = 1; it != albums.end(); i++, it++) {
        std::cout << *it << "\n";
    }

    string albums2 = calculate2(players);
    std::cout << "Albums: \n" << albums2;
    string albums3 = calculate3(players);
    std::cout << "\nAlbums: \n" << albums2;
    return 0;
}