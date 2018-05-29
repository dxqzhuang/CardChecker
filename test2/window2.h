#ifndef WINDOW2_H
#define WINDOW2_H

#include <QMainWindow>
#include <string>
#include <map>
#include <regex>
#include <iostream>
#include <ctime>
#include <database.h>

namespace Ui {
    class window2;
}

using namespace std;
class window2 : public QMainWindow
{
    Q_OBJECT

    public:
        explicit window2(database& databs, QWidget *parent = 0);
        ~window2();

    private slots:
    void window2_check_btn_pressed();

    private:
        Ui::window2 *ui;
        database& db;

        void connectSignalsSlots();

        bool checkLuhn(const std::string &input);
        string detectCardType(string number);

};

#endif // WINDOW2_H
