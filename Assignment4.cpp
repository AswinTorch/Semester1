#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

class Card {
    char m_char; //'S', 'C', 'D' 'H'
    int m_num; //Values
public:
    Card(const char suit = 'S', const int number = 0) : m_char (suit), m_num (number){ }
    friend ostream& operator << (ostream&, const Card&);
};

ostream& operator << (ostream& o, const Card& c){
    o << c.m_char;
    switch (c.m_num){
        case 1: o << 'A'; break;
        case 11: o << 'J'; break;
        case 12: o << 'Q'; break;
        case 13: o << 'K'; break;
        default: o << c.m_num;
    }
    return o;
}

class Player {
    string m_name;
    vector <Card> m_deck;
public:
    Player (const string& n = "") : m_name (n) { m_deck.reserve(5); }
    void push_back(const Card& c){ m_deck.push_back(c); }
    friend ostream& operator << (ostream&, const Player& p);
};
ostream& operator << (ostream& o, const Player& p){
    o << "Player " << p.m_name << " has ";
    for (int a = 0; a < p.m_deck.size(); ++a) {
        o << p.m_deck[a] << " ";
    }
    return o;
}

int main (){
    vector <Card> deck; deck.reserve(52);
    for (int a = 1; a <= 13; ++a) { deck.push_back(Card ('S', a)); }
    for (int a = 1; a <= 13; ++a) { deck.push_back(Card ('D', a)); }
    for (int a = 1; a <= 13; ++a) { deck.push_back(Card ('H', a)); }
    for (int a = 1; a <= 13; ++a) { deck.push_back(Card ('C', a)); }
    random_shuffle(deck.begin(), deck.end());

    vector <Player> players;
    players.push_back(Player("0"));
    players.push_back(Player("1"));
    players.push_back(Player("2"));
    players.push_back(Player("3"));
    players.push_back(Player("4"));

    for (int a = 0; a < players.size(); ++a) {
        for (int b = 0; b < 7; ++b) {
            Card c = deck.back();
            players[a].push_back(c);
            deck.pop_back();
        }
    }

    for (int a = 0; a < players.size(); ++a) {
        cout << players[a] << endl;
    }

}
