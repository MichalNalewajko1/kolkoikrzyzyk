#include "logika.h"
#include <algorithm>

TicTacToeLogic::TicTacToeLogic() {
    ai = 'O';
    resetBoard();
}

void TicTacToeLogic::resetBoard() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = '_';
        }
    }
}

bool TicTacToeLogic::isMoveLeft(char b[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == '_')
                return true;
    return false;
}

int TicTacToeLogic::evaluate(char b[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == ai) return +10;
            else if (b[row][0] == 'X') return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == ai) return +10;
            else if (b[0][col] == 'X') return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == ai) return +10;
        else if (b[0][0] == 'X') return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == ai) return +10;
        else if (b[0][2] == 'X') return -10;
    }
    return 0;
}

int TicTacToeLogic::minimax(char b[3][3], int depth, bool isMax) {
    int score = evaluate(b);

    if (score == 10) return score;
    if (score == -10) return score;
    if (!isMoveLeft(b)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == '_') {
                    b[i][j] = ai;
                    best = std::max(best, minimax(b, depth + 1, !isMax));
                    b[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == '_') {
                    b[i][j] = 'X';
                    best = std::min(best, minimax(b, depth + 1, !isMax));
                    b[i][j] = '_';
                }
            }
        }
        return best;
    }
}

GameMove TicTacToeLogic::findBestMove(char b[3][3]) {
    int bestVal = -1000;
    GameMove bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == '_') {
                b[i][j] = ai;
                int moveVal = minimax(b, 0, false);
                b[i][j] = '_';

                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

GameMove TicTacToeLogic::getComputerMove(char b[3][3], int difficultyLevel) {
    if (difficultyLevel == 1) {
        return findRandomMove(b);
    }
    else if (difficultyLevel == 2) {
        int szansa = rand() % 100;
        if (szansa < 50) {
            return findBestMove(b);
        } else {
            return findRandomMove(b);
        }
    }
    else {
        return findBestMove(b);
    }
}

GameMove TicTacToeLogic::findRandomMove(char b[3][3]) {
    GameMove randomMove;
    while (true) {
        int r = rand() % 3;
        int c = rand() % 3;

        if (b[r][c] == '_') {
            randomMove.row = r;
            randomMove.col = c;
            return randomMove;
        }
    }
}