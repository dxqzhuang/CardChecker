#include "window4.h"
#include "ui_window4.h"

window4::window4(database& databs, vector<map<string,string>>data, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window4),
    db(databs)
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
    connectSignalsSlots();
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
    for(int i=0; i<tables.size();i++)
        delete tables[i];
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
        cout << "table size: " << tableptr->size().width() << tableptr->size().height() << endl;
        tables.push_back(tableptr);
        cout << "table generated!!!" << endl;

        //2. generate a new tab with this table in it
        ui->window4_tabs_widget->addTab(tableptr,QString::fromStdString(sortedData[i][0]["bankName"]));
        ui->window4_tabs_widget->setContentsMargins(0,0,0,0);
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
    //table->resize(table->parentWidget()->size());
    //table->resize(ui->centralwidget->size());
    table->resizeColumnsToContents();
    table->resize(ui->window4_tabs_widget->size());
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
    table->setColumnWidth(0,table->size().width()/2);
    table->setColumnWidth(1,table->size().width()/2);
    cout << "generateTable: i finished!" << endl;
}

void window4::connectSignalsSlots()
{
    connect(ui->window4_save_btn, SIGNAL(pressed()),this,SLOT(window4_save_btn_pressed()));
}

void window4::window4_save_btn_pressed()
{
    QString outputFileName(QDir::currentPath()+QString::fromStdString("/table.pdf"));
    QString strStream;
    QTextStream out(&strStream);

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<div>Made with pride by:<br>Jack Hou<br>David Zhuang</div>"
        "<table border=1 cellspacing=0 cellpadding=2 style='width: 800px; margin:5px auto;'>\n";
    for(int i=0; i<tables.size(); i++)
    {

        const int rowCount = tables[i]->rowCount();
        const int columnCount = tables[i]->columnCount();

        // headers
        // data table
        for (int row = 0; row < rowCount; row++){
            out << "<tr>";
            string bankName, cardLevel;
            //!!!DANGER!!
            //! //cout << "row:" << row << ";col: " << column << ";text: " << tables[i]->itemAt(row,column)->text().toStdString() << endl;
            string cardNumber = tables[i]->itemAt(row,0)->text().toStdString();
            cout << "cardNumber: "  << cardNumber;
            cout << "index:" << i << endl;
            db.whichBankIssuedThis(QString::fromStdString(cardNumber), bankName, cardLevel);
            cout << "bankName: " << bankName << " ; cardLevel: " << cardLevel << endl;

            //1. print card number
            out << QString("<td bkcolor=0>"+QString::fromStdString(cardNumber)+"</td>");

            //2. print bank name
            out << QString("<td bkcolor=0>"+QString::fromStdString(bankName)+"</td>");

            //3. print card level(type)
            out << QString("<td bkcolor=0>"+QString::fromStdString(cardLevel)+"</td>");


//            for (int column = 0; column < columnCount; column++){
//                if (!tables[i]->isColumnHidden(column)) {
//                    out << QString("<td bkcolor=0>%1</td>").arg(tables[i]->item(row,column)->text());
//                }
//            }
            out << "</tr>\n";
        }
    }


    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    printer.setOutputFileName(outputFileName);
    document->print(&printer);

    delete document;

    QMessageBox box;
    QString str;
    str.append("Outputted to: ");
    str.append(outputFileName);
    box.setText(str);
    box.exec();
}
