#ifndef LOGIKA_H
#define LOGIKA_H

#include <cstdlib>

struct GameMove {
    int row;
    int col;
};

class TicTacToeLogic {
public:
    TicTacToeLogic();
    void resetBoard();

    char board[3][3];
    char ai;

    bool isMoveLeft(char b[3][3]);
    int evaluate(char b[3][3]);
    int minimax(char b[3][3], int depth, bool isMax);
    GameMove findBestMove(char b[3][3]);
    GameMove findRandomMove(char b[3][3]);
    GameMove getComputerMove(char b[3][3], int difficultyLevel);
};

#endif // LOGIKA_H
