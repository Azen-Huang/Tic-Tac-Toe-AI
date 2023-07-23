#include <string>
#include <vector>
#include <iostream>
using namespace std;
#define SIZE 3

class Game {
public:
    Game();
    Game(char _trun);
    void move(int action);
    void undo(int action);
    int score(); // win(10), lose(-10), draw(0), other(-1)
    vector<int> getValidAction();
    void print();

    char trun;
private:
    string board;
};