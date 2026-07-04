#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

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

    // Style przycisku RESET
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

    gra.board[row][col] = 'X';

    sprawdz();

    if (!gra.isMoveLeft(gra.board) || gra.evaluate(gra.board) != 0) return;

    int wybranyPoziom = ui->wyborTrudnosci->currentIndex() + 1;
    GameMove bestMove = gra.getComputerMove(gra.board, wybranyPoziom);

    int aiIndex = bestMove.row * 3 + bestMove.col;

    gra.board[bestMove.row][bestMove.col] = 'O';

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

    gra.resetBoard();
}

void MainWindow::on_p1_clicked() { klikniecie(ui->p1); }
void MainWindow::on_p2_clicked() { klikniecie(ui->p2); }
void MainWindow::on_p3_clicked() { klikniecie(ui->p3); }
void MainWindow::on_p4_clicked() { klikniecie(ui->p4); }
void MainWindow::on_p5_clicked() { klikniecie(ui->p5); }
void MainWindow::on_p6_clicked() { klikniecie(ui->p6); }
void MainWindow::on_p7_clicked() { klikniecie(ui->p7); }
void MainWindow::on_p8_clicked() { klikniecie(ui->p8); }
void MainWindow::on_p9_clicked() { klikniecie(ui->p9); }