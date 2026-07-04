#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <algorithm>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    przyciski[0] = ui->p1;
    przyciski[1] = ui->p2;
    przyciski[2] = ui->p3;
    przyciski[3] = ui->p4;
    przyciski[4] = ui->p5;
    przyciski[5] = ui->p6;
    przyciski[6] = ui->p7;
    przyciski[7] = ui->p8;
    przyciski[8] = ui->p9;
    srand(time(NULL));


    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   font-size: 22px;"
        "   font-weight: bold;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #962d22;"
        "}"
        );
    this->setStyleSheet("QMainWindow { background-color: #f5f6fa; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sprawdz()
{
    const int kombinacje[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    QString wygrany = "";

    for (int i = 0; i < 8; ++i) {
        QString p1 = przyciski[kombinacje[i][0]]->property("gracz").toString();
        QString p2 = przyciski[kombinacje[i][1]]->property("gracz").toString();
        QString p3 = przyciski[kombinacje[i][2]]->property("gracz").toString();

        if (p1 == p2 && p2 == p3 && p1 != "") {
            wygrany = p1;
            break;
        }
    }
    if (wygrany != "") {
        for(int i = 0; i < 9; i++) {
            przyciski[i]->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        }
        QMessageBox::information(this, "Koniec gry!", "Wygrywa gracz: " + wygrany + "!");
        return;
    }
    bool pelnaPlansza = true;
    for(int i = 0; i < 9; i++) {
        if (przyciski[i]->property("gracz").toString() == "") {
            pelnaPlansza = false;
            break;
        }
    }
    if (pelnaPlansza) {
        QMessageBox::information(this, "Koniec gry!", "Mamy remis!");
    }
}
void MainWindow::klikniecie(QPushButton *przycisk)
{
    if (przycisk->property("gracz").toString() != "") return;

    int index = -1;
    for (int i = 0; i < 9; i++) {
        if (przyciski[i] == przycisk) {
            index = i;
            break;
        }
    }
    if (index == -1) return;

    int row = index / 3;
    int col = index % 3;

    przycisk->setIcon(QIcon(":/img/x.bmp"));
    przycisk->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    przycisk->setProperty("gracz", "X");

    board[row][col] = 'X';

    sprawdz();

    if (!isMoveLeft(board) || evaluate(board) != 0) return;

    int wybranyPoziom = ui->wyborTrudnosci->currentIndex()+1;
    Move bestMove = getComputerMove(board, wybranyPoziom);


    int aiIndex = bestMove.row * 3 + bestMove.col;

    board[bestMove.row][bestMove.col] = 'O';


    przyciski[aiIndex]->setIcon(QIcon(":/img/o.bmp"));
    przyciski[aiIndex]->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    przyciski[aiIndex]->setProperty("gracz", "O");

    sprawdz();
}


void MainWindow::on_pushButton_clicked()
{
    aktualnyGracz = 'X';
    ui->turaGracza->setPixmap(QPixmap(":/img/xsmall.bmp"));


    for(int i = 0; i < 9; i++){
        przyciski[i]->setIcon(QIcon(":/img/nic.bmp"));
        przyciski[i]->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        przyciski[i]->setProperty("gracz", "");
    }

    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            board[i][j] = '_';
        }
    }
}


void MainWindow::on_p1_clicked()
{
    klikniecie(ui->p1);
}

void MainWindow::on_p2_clicked()
{
    klikniecie(ui->p2);
}

void MainWindow::on_p3_clicked()
{
    klikniecie(ui->p3);
}
void MainWindow::on_p4_clicked()
{
    klikniecie(ui->p4);
}
void MainWindow::on_p5_clicked()
{
    klikniecie(ui->p5);
}
void MainWindow::on_p6_clicked()
{
    klikniecie(ui->p6);
}
void MainWindow::on_p7_clicked()
{
    klikniecie(ui->p7);
}
void MainWindow::on_p8_clicked()
{
    klikniecie(ui->p8);
}
void MainWindow::on_p9_clicked()
{
    klikniecie(ui->p9);
}


bool MainWindow::isMoveLeft(char b[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == '_')
                return true;
    return false;
}

int MainWindow::evaluate(char b[3][3]) {
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

int MainWindow::minimax(char b[3][3], int depth, bool isMax) {
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
MainWindow::Move MainWindow::findBestMove(char b[3][3]) {
    int bestVal = -1000;
    Move bestMove;
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

MainWindow::Move MainWindow::getComputerMove(char b[3][3], int difficultyLevel) {

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

void MainWindow::resetBoard() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = '_';
        }
    }
    aktualnyGracz = 'X';
}
MainWindow::Move MainWindow::findRandomMove(char b[3][3]) {
    Move randomMove;

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
