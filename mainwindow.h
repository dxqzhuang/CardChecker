#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <regex>
#include <map>
#include <numeric>
#include <vector>
#include <sstream>
#include <ctime>

namespace Ui {
class MainWindow;
}

using namespace std;
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
    string detectCardType(string number);
    string generateCardNum(string bin, int len);


private slots:
    void checkInput();

};

#endif // MAINWINDOW_H
