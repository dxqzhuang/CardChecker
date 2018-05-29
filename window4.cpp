#include "window4.h"
#include "ui_window4.h"

window4::window4(vector<map<string,string>>data, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window4)
{
    /**
      data MUST follow this format:
      [ //vector(note: 1D)
          { //map
            {"cardNumber","123"},
            {"cardType","gold"},
            {"bankName","BofA"}
          },
          ...
      ]


      */
    ui->setupUi(this);
    cout << "data received on window 4!!" << endl;
    for(int i=0; i<data.size();i++)
    {
        cout << "data[i]: " << data[i]["cardNumber"] << "; "<<data[i]["bankName"] << endl;
    }
    sortData(data); //after receiving the data, sort it first so that it can be displayed
    cout << "sort data finished!!" << endl;
    //clear up the two junk tabs
    ui->window4_tabs_widget->removeTab(0);
    ui->window4_tabs_widget->removeTab(0);
    generateTabs();
}



window4::~window4()
{
    delete ui;
}

void window4::generateTabs()
{
    /**
     * generates all tabs and display them
     * @pre sortedData variable has to be a sorted vector!
     *  each inner vector must contain cards from ONE bank only!!!
     * @dependency: generateTable()
     */

    cout << "generateTab fired!!!" << endl;
    //loop through each inner vector(bank)
    for(int i=0; i<sortedData.size(); i++)
    {
        cout << "now we have " << ui->window4_tabs_widget->count() << " tabs" << endl;
        cout << "generateTab for loop: " << i << endl;
//        for(int j=0; j<sortedData[i].size();j++)
//            cout << sortedData[i][j]["cardNumber"] << sortedData[i][j]["bankName"] << endl;
        //1. generate a table and fill it with cards of this bank
        QTableWidget*tableptr = new QTableWidget();
        generateTable(sortedData[i],tableptr);
        cout << "table generated!!!" << endl;

        //2. generate a new tab with this table in it
        ui->window4_tabs_widget->addTab(tableptr,QString::fromStdString(sortedData[i][0]["bankName"]));
        cout << "now we have " << ui->window4_tabs_widget->count() << " tabs" << endl;

    };
}

void window4::sortData(vector<map<string,string>>&data)
{
    /**
      @brief generate the sorted data then fill the sortedData private variable.
      data will be sorted based on bank name. All cards issued by the same bank
      will be pushed into one vector.
      @example:
      [ //outer vector of sortedData(note: 2D)
        [   //inner vector or sortedData
            {   //entry 1
                {"cardNumber","123"},
                {"cardType","gold"},
                {"bankName","BofA"}
            },
            {   //entry 2
                {"cardNumber","193"},
                {"cardType","classic"},
                {"bankName","BofA"}
            },
        ],
        [   //inner vector or sortedData
            {   //entry 1
                {"cardNumber","453"},
                {"cardType","silver"},
                {"bankName","cityBank"}
            },
            {   //entry 2
                {"cardNumber","596"},
                {"cardType","Classical"},
                {"bankName","citiBank"}
            },
        ]
      ]
      @dependency:<algorithm> <vector> <map> <string>
      */

    //1. sort data(1D vector) based on first letter of bankName
    std::sort(data.begin(),data.end(), [](map<string,string>a,map<string,string>b){
        return a["bankName"][0] < b["bankName"][0];
    });

    //2. loop through data, push each card issued by same bank
    //     into one vector then remove it from data vector
    while(data.size())
    {
        vector<map<string,string>> lst; //will be pushed into sortedData at the end of iteration
        string bankName(data[0]["bankName"]);//keep track of the bank name for this iteration
        //---process-----
        //push the first entry to lst,  then erase it
        lst.push_back(data[0]);
        data.erase(data.begin());
        while(data.size()&&data[0]["bankName"]==bankName)   //as long as next entry have the same bank name
        {
            lst.push_back(data[0]);
            data.erase(data.begin());    //remove the entry from data after pushing it to lst
        }
        sortedData.push_back(lst);
    }
}

void window4::generateTable(vector<map<string, string>>table_data, QTableWidget *table)
{
    /**
      @brief given a vector of cards(by ONE bank),generate a table,
            fill it with given data, then return a reference to the table.
      @param table data: vector of cards; see below
                [
                    {   //entry 1
                        {"cardNumber","123"},
                        {"cardType","gold"},
                        {"bankName","BofA"}
                    },
                    {   //entry 2
                        {"cardNumber","193"},
                        {"cardType","classic"},
                        {"bankName","BofA"}
                    },
                ]
        @note each table has two columns: cardNumber and cardType
        @dependency: <QstringList> <vector> <map>
      */

    //2 columns; as many rows as there are entries
    table->setRowCount(table_data.size());
    cout << "table_data.size: " << table_data.size() << endl;
    table->setColumnCount(2);
    //1. create horizontal header
    QStringList labels;
    labels << tr("Card number") << tr("Card type");
    table->setHorizontalHeaderLabels(labels);
    //table.horizontalHeader()-setResizeMode(0, QHeaderView::Stretch);
    table->verticalHeader()->hide();


    cout << "table row count.size: " << table->rowCount() << endl;
    //2. add rows
    for(int i=0; i<table->rowCount();i++)
    {
        cout << "generateTable for loop: " << i << endl;
        //card number, card type
        QTableWidgetItem *cardNumItem = new QTableWidgetItem(QString::fromStdString(table_data[i]["cardNumber"]));
        QTableWidgetItem *cardTypeItem = new QTableWidgetItem(QString::fromStdString(table_data[i]["cardType"]));
        table->setItem(i,0,cardNumItem);
        table->setItem(i,1,cardTypeItem);
    }
    cout << "generateTable: i finished!" << endl;
}