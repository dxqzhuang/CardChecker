#ifndef WINDOW4_H
#define WINDOW4_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <qtabwidget.h>
#include <qtablewidget.h>
#include <QStringList>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <database.h>
#include <QPainter>
#include <QtPrintSupport/QPrinter>;
#include <QTextStream>
#include <QTextDocument>
#include <QDir>


namespace Ui {
class window4;
}
using namespace std;

//======this is only a display window. No generating is done in here.
class window4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit window4(vector<map<string,string>>data, QWidget *parent = 0);
    /** FOLLOW THIS FORMAT!!!
      [ //vector
          { //map
            {"cardNumber","123"},
            {"cardType","gold"},
            {"bankName","BofA"}
          },
          ...
      ]



      */

    ~window4();

private slots:
    void window4_save_btn_pressed();


private:
    Ui::window4 *ui;
    void generateTabs();
    void connectSignalsSlots();
    void sortData(vector<map<string,string>>&data);
    void generateTable(vector<map<string, string>>table_data, QTableWidget* table);
    //vector of vectors, each inner vector containing all cards from ONE bank only.
    //each inner vector will be displayed separately in a tab.
    vector<vector<map<string,string>>> sortedData;
    vector<QTableWidget*> tables;
};

#endif // WINDOW4_H