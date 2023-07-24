#include <iostream>
#include <vector>
#include <cmath>
#include "game.h"
using namespace std;
#define SIZE 3
#define DEBUG

int alphabeta(Game board, int alpha, int beta) {
    vector<int> validAction = board.getValidAction();
    for (const int& mov : validAction) {
        board.move(mov);
        int score = board.score();
        if (board.score() != -1) {
            return board.score();
        }
        score = -alphabeta(board, -beta, -alpha);
        if (score >= beta) {
            return score;
        }
        if (score > alpha) {
            alpha = score;
        }
        board.undo(mov);
    }
    return alpha;
}

int minimax(Game board) {
    int score = board.score();
    if (score != -1) {
        return score;
    }

    int bestScore = -1000;
    vector<int> validAction = board.getValidAction();
    for (const int& mov : validAction) {
        board.move(mov);
        int score = minimax(board);
        bestScore = max(bestScore, score);
        board.undo(mov);
    }

    return -bestScore;
}

int getBestAction(Game board, int alpha = -1000, int beta = 1000) {
    int bestScore = -1000;
    int bestAction;
    vector<int> validAction = board.getValidAction();
    for (const int& action : validAction) {
        board.move(action);
        // int score = minimax(board);
        int score = -alphabeta(board, -beta, -alpha);
        board.undo(action);
        if (score > alpha) { // alphabeta
            alpha = score;
            bestAction = action;
        }
        // if (score > bestScore) { // minimax
        //     bestScore = score;
        //     bestAction = action;
        // }
    }
    return bestAction;
}

int input(string input) {
    return (toupper(input[0]) - 'A') + (input[1] - '1') * SIZE;
}

void AI_vs_AI() {
    Game board = Game();
    board.print();
    int score = board.score();
    while (score == -1) {
        int action = getBestAction(board);
        board.move(action);
        board.print();
        score = board.score();
    }
    char winner = board.turn == 'O' ? 'X' : 'O';
    if (score == 0) {
        cout << "Draw" << endl;
    }
    else {
        cout << "Winner is " << winner << "." << endl;
    }
    return;
}

void Human_vs_Human() {
    Game board = Game();
    string actionString;
    board.print();
    while (getline(cin, actionString)) {
        int action = input(actionString);
        board.move(action);
        board.print();
        cout << "Action: " << actionString << endl;
        int score = board.score();
        if (score != -1) {
            char winner = board.turn == 'O' ? 'X' : 'O';
            if (score == 0) {
                cout << "Draw" << endl;
            }
            else {
                cout << "Winner is " << winner << "." << endl;
            }
            return;
        }
    }
}

void Human_vs_AI() {
    Game board = Game();
    string actionString;
    board.print();
    cout << "Who first? (1. AI, 2. Human)" << endl;
    getline(cin, actionString);
    if (actionString == "1") {
        int AI_Action = getBestAction(board);
        board.move(AI_Action);
        board.print();
    }
    while (getline(cin, actionString)) {
        int action = input(actionString);
        board.move(action);
        board.print();

        int AI_Action = getBestAction(board);
        board.move(AI_Action);
        board.print();
        
        int score = board.score();
        if (score != -1) {
            char winner = board.turn == 'O' ? 'X' : 'O';
            if (score) {
                cout << "Winner is " << winner << "." << endl;
            }
            else {
                cout << "Draw" << endl;
            }
            return;
        }
    }
}

int main() {
    string command;
    bool firstPlayerturn = true;
    cout << "1. Human vs. Human" << endl;
    cout << "2. Human vs. AI" << endl;
    cout << "3. AI vs AI" << endl;
    cout << "Input Command: ";
    while (getline(cin, command)) {
        if (command == "1") {
            cout << "Start Human vs. Human" << endl;
            Human_vs_Human();
        }
        else if (command == "2") {
            cout << "Start Human vs. AI" << endl;
            Human_vs_AI();
        }
        else if (command == "3") {
            cout << "Start AI vs. AI" << endl;
            AI_vs_AI();
        }
        else {
            exit(0);
        }
        
    }
    return 0;
}