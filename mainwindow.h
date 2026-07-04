#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_p1_clicked();

    void on_p2_clicked();

    void on_p4_clicked();

    void on_p3_clicked();

    void on_p5_clicked();

    void on_p6_clicked();

    void on_p7_clicked();

    void on_p8_clicked();

    void on_p9_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    char aktualnyGracz = 'X';
    char ai = 'O';
    char board[3][3] = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };
    QPushButton *przyciski[9];
    void klikniecie(QPushButton *przycisk);
    void sprawdz();
    struct Move{
        int row, col;
    };
    bool isMoveLeft(char[3][3]);
    int evaluate(char b[3][3]);
    int minimax(char b[3][3], int depth, bool isMax);
    Move findBestMove(char b[3][3]);
    Move getComputerMove(char b[3][3], int difficultyLevel);
    Move findRandomMove(char b[3][3]);
    void resetBoard();
};
#endif // MAINWINDOW_H
