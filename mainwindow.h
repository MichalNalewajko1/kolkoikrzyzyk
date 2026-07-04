#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "logika.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_p1_clicked();
    void on_p2_clicked();
    void on_p3_clicked();
    void on_p4_clicked();
    void on_p5_clicked();
    void on_p6_clicked();
    void on_p7_clicked();
    void on_p8_clicked();
    void on_p9_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *przyciski[9];
    char aktualnyGracz = 'X';

    TicTacToeLogic gra;

    void klikniecie(QPushButton *przycisk);
    void sprawdz();
};
#endif // MAINWINDOW_H