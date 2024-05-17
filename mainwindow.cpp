#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateATM(char id, int value)
{
    QMutexLocker locker(&mutex);

    int balance = ui->spinBox_A->value();
    if (id == 'A')
        balance += value;
    else if (id == 'B')
        balance = ui->spinBox_B->value() + value;
    else if (id == 'C')
        balance = ui->spinBox_C->value() + value;

    if (balance < 0)
    {
        QMessageBox::critical(this, "Error", "Balance cannot be negative!");
        return;
    }

    if (id == 'A')
        ui->spinBox_A->setValue(balance);
    else if (id == 'B')
        ui->spinBox_B->setValue(balance);
    else if (id == 'C')
        ui->spinBox_C->setValue(balance);
}

void MainWindow::on_pushButton_clicked()
{
    int valueA = ui->spinBox_valueA->value();
    int valueB = ui->spinBox_valueB->value();
    int valueC = ui->spinBox_valueC->value();

    QThread* threadA = new QThread();
    QThread* threadB = new QThread();
    QThread* threadC = new QThread();

    connect(threadA, &QThread::started, [this, valueA](){
        updateATM('A', valueA);
    });
    connect(threadB, &QThread::started, [this, valueB](){
        updateATM('B', valueB);

    });
    connect(threadC, &QThread::started, [this, valueC](){
        updateATM('C', valueC);
    });

    connect(threadA, &QThread::finished, threadA, &QThread::deleteLater);
    connect(threadB, &QThread::finished, threadB, &QThread::deleteLater);
    connect(threadC, &QThread::finished, threadC, &QThread::deleteLater);

    threadA->start();
    threadB->start();
    threadC->start();
}
void MainWindow::on_pushButton_1_clicked()
{
    int valueA = ui->spinBox_valueA->value();
    int valueB = ui->spinBox_valueB->value();
    int valueC = ui->spinBox_valueC->value();

    QString idA = ui->comboBox->currentText();
    QString idB = ui->comboBox_2->currentText();
    QString idC = ui->comboBox_3->currentText();
    if (idB == idA || idC == idA || idC == idB)
    {
        QMessageBox::critical(this, "Error", "Each ATM must have a unique identifier!");
        return;
    }

    QThread* threadA = new QThread();
    QThread* threadB = new QThread();
    QThread* threadC = new QThread();

    connect(threadA, &QThread::started, [this, valueA, idA](){
        transfer(idA, valueA);
    });
    connect(threadB, &QThread::started, [this, valueB, idB](){
        transfer(idB, valueB);
    });
    connect(threadC, &QThread::started, [this, valueC, idC](){
        transfer(idC, valueC);
    });

    connect(threadA, &QThread::finished, threadA, &QThread::deleteLater);
    connect(threadB, &QThread::finished, threadB, &QThread::deleteLater);
    connect(threadC, &QThread::finished, threadC, &QThread::deleteLater);

    threadA->start();
    threadB->start();
    threadC->start();
}

void MainWindow::transfer(const QString& id, int value)
{
    QMutexLocker locker(&mutex);

    if (id == "AA")
    {
        if (ui->spinBox_A->value() >= value)
        {
            ui->spinBox_A->setValue(ui->spinBox_A->value() - value);
            ui->spinBox_A->setValue(ui->spinBox_A->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM A!");
    }
    else if (id == "AB")
    {
        if (ui->spinBox_A->value() >= value)
        {
            ui->spinBox_A->setValue(ui->spinBox_A->value() - value);
            ui->spinBox_B->setValue(ui->spinBox_B->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM B!");
    }
    else if (id == "AC")
    {
        if (ui->spinBox_A->value() >= value)
        {
            ui->spinBox_A->setValue(ui->spinBox_A->value() - value);
            ui->spinBox_C->setValue(ui->spinBox_C->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM C!");
    }
    else if (id == "BA")
    {
        if (ui->spinBox_B->value() >= value)
        {
            ui->spinBox_B->setValue(ui->spinBox_B->value() - value);
            ui->spinBox_A->setValue(ui->spinBox_A->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM A!");
    }
    else if (id == "BB")
    {
        if (ui->spinBox_B->value() >= value)
        {
            ui->spinBox_B->setValue(ui->spinBox_B->value() - value);
            ui->spinBox_B->setValue(ui->spinBox_B->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM B!");
    }
    else if (id == "BC")
    {
        if (ui->spinBox_B->value() >= value)
        {
            ui->spinBox_B->setValue(ui->spinBox_B->value() - value);
            ui->spinBox_C->setValue(ui->spinBox_C->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM C!");
    }
    else if (id == "CA")
    {
        if (ui->spinBox_C->value() >= value)
        {
            ui->spinBox_C->setValue(ui->spinBox_C->value() - value);
            ui->spinBox_A->setValue(ui->spinBox_A->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM A!");
    }
    else if (id == "CB")
    {
        if (ui->spinBox_C->value() >= value)
        {
            ui->spinBox_C->setValue(ui->spinBox_C->value() - value);
            ui->spinBox_B->setValue(ui->spinBox_B->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM B!");
    }
    else if (id == "CC")
    {
        if (ui->spinBox_C->value() >= value)
        {
            ui->spinBox_C->setValue(ui->spinBox_C->value() - value);
            ui->spinBox_C->setValue(ui->spinBox_C->value() + value);
        }
        else
            QMessageBox::critical(this, "Error", "Not enough balance in ATM C!");
    }
    else
        QMessageBox::critical(this, "Error", "Invalid ATM identifier!");
}
