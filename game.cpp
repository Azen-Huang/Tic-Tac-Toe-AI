#include "game.h"

Game::Game() {
    board = "---------";
    turn = 'O';
}

Game::Game(char _turn) {
    board = "---------";
    turn = _turn;
}

void Game::move(int action) {
    board[action] = turn;
    turn = turn == 'O' ? 'X' : 'O';
}

void Game::undo(int action) {
    board[action] = '-';
    turn = turn == 'O' ? 'X' : 'O';
}

int Game::score(){ // O win(10), lose(-10), draw(0), other(-1)
    const int winningCombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, //row
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // col
        {0, 4, 8}, {2, 4, 6} // Diagonal
    };

    for (auto& winningCombination : winningCombinations) {
        if (board[winningCombination[0]] != '-' && 
            board[winningCombination[0]] == board[winningCombination[1]] && 
            board[winningCombination[1]] == board[winningCombination[2]]) {
                return 10;
            }
    }
    if (board.find('-') == string::npos) {
        return 0;
    }
    
    return -1;
}

vector<int> Game::getValidAction() {
    vector<int> validAction;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == '-') {
            validAction.push_back(i);
        }
    }
    return validAction;
}

void Game::print() {
    for (char c = 'A'; c <= 'C'; ++c) {
        cout << "  " << c << " ";
    }
    cout << endl;
    cout << "+---+---+---+" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << "|";
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << board[i * SIZE + j] << " |";
        }
        cout << " " << i + 1 << endl;
        cout << "+---+---+---+" << endl;
    }
    return;
}
