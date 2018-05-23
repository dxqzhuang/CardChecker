#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <string>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::string numberInput;


protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    void connectSignalsSlots();
    bool checkLuhn(const std::string &input);

private slots:
    void checkInput();

};

#endif // MAINWINDOW_H
