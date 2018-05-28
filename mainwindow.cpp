#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSignalsSlots();
    std::cout << generateCardNum("473705",16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignalsSlots()
{
    connect(ui->checkButton,SIGNAL(pressed()), this,SLOT(checkInput()));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::checkInput(){
    //std::cout << "button clicked" << std::endl;
    std::string input=ui->inputField->text().toUtf8().constData();
    std::cout << "number input: " << input << std::endl;


    if(checkLuhn(input)){
        std::cout<<"what";
        std::cout<<input;
//        QDialog::
    }
    else{
        std::cout<<"huh?";
    }
}

bool MainWindow::checkLuhn(const std::string &input){
    int sum=0;
    bool second=false;
    for(int i=input.length()-1; i>=0; --i){     //starting from the right end
        int d = input[i] - 'a';                 //ASCII string to int
        if(second == true)       d=d*2;         //double every second digit
        sum+=d/10;                              //if result of doubling > 10
        sum+=d%10;                              //add two digits of result
        second=!second;                         //alternating bool
    }
    std::cout<<"here";
    return (sum%10 == 0);
}

string MainWindow::detectCardType(string number)
{
    /**
      @dependencies: <regex>, <string>, <map>, <ctime>
      @return string of card type. ex: "discover"
      */
    map<string, regex> types{
        {"electron", regex("^(4026|417500|4405|4508|4844|4913|4917)\d+$")},
        {"maestro", regex("^(5018|5020|5038|5612|5893|6304|6759|6761|6762|6763|0604|6390)\d+$")},
        {"dankort", regex("^(5019)\d+$")},
        {"interpayment", regex("^(636)\d+$")},
        {"unionpay",regex("^(62|88)\d+$")},
        {"visa",regex("^4[0-9]{12}(?:[0-9]{3})?$")},
        {"mastercard",regex("^5[1-5][0-9]{14}$")},
        {"amex",regex("^3[47][0-9]{13}$")},
        {"diners",regex("^3(?:0[0-5]|[68][0-9])[0-9]{11}$")},
        {"discover",regex("^6(?:011|5[0-9]{2})[0-9]{12}$")},
        {"jcb",regex("^(?:2131|1800|35\d{3})\d{11}$")}
    };
    cout << "your card number: " << number << endl;
    for(auto it:types)
    {
        //cout << it.first << endl;
        if(regex_search(number,it.second))
        {
            cout << "your card is: "<<it.first << endl;
            return it.first;
        }
        else
            cout << "your card is not: " << it.first << endl;
    }
    return "NONE";

}


string MainWindow::generateCardNum(string bin, int len)
{
    /**
     * @brief generate credit card number based on first 6 digits and required length
     * @param len: length of card number(including bin and checkdigit)
     * @note check sum explained at https://www.sapling.com/7966257/checksum-credit-card
     */
    srand(time(NULL));
    vector<int> num, temp;
    int i=0,j=0;
    for(auto k:bin) num.push_back(k-'0');
    for(;i++<len-7;)
        num.push_back(rand()%10);
    for(temp=num,i=num.size();i-->0;)
        if(i%2==0 && (num[i]*=2)>9)//if it's a two digit number
            num[i] = num[i]/10 + num[i]%10;
    temp.push_back((j=i=accumulate(num.begin(),num.end(),0))%10==0&&(i/10)%2==0?0:10+10*(i/10)-j);
    return accumulate(temp.begin(),temp.end(),string(), [](string a, int b){return a+to_string(b);});
}
