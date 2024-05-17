#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_1_clicked();

private:
    Ui::MainWindow *ui;
    QMutex mutex;
    void updateATM(char id, int value);
    void transfer(const QString& id, int value);

};

#endif // MAINWINDOW_H
