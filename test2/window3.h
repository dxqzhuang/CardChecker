#ifndef window3_H
#define window3_H

#include <QMainWindow>
#include <window4.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <database.h>


using namespace std;
namespace Ui {
    class window3;
}

class window3 : public QMainWindow
{
    Q_OBJECT

    public:
        explicit window3(database& databs, QWidget *parent = 0);
        ~window3();

    private slots:
    void window3_generate_btn_pressed();
    void packUpEntryRequirement();
    void window3_newEntry_btn_pressed();
    private:
        Ui::window3 *ui;
        window4 *wind4;
        vector<map<string,string>>data; //SEE THE FORMAT IN WINDOW 4
        void generateData(vector<map<string,string>>& data,
                          vector<map<string,string>>entryRequirements);
        string findBinNumber(string cardType, string bankName);
        int cardNumLen(string cardType);
        void connectSignalsSlots();
        string generateCardNum(string bin, int len);
        database& db;
        QString binFind(const QString &name, char type);
        int search(const QString &name, char type);
        vector<map<string,string>>entryRequirements;
        void fillBankList();

};

#endif // window3_H
