#include "window2.h"
#include "ui_window2.h"

window2::window2(database &databs, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window2),
    db(databs)
{
    ui->setupUi(this);
    connectSignalsSlots();
}

window2::~window2()
{
    delete ui;
}


void window2::connectSignalsSlots()
{
    connect(ui->window2_check_btn, SIGNAL(pressed()),this, SLOT(window2_check_btn_pressed()));
}

void window2::window2_check_btn_pressed()
{
    std::string input = ui->window2_input_field->text().toUtf8().constData();
    if(checkLuhn(input))
    {
        ui->window2_result_field->append("CONGRATULATIONS! YOU HAVE A VALID CARD\n");
        ui->window2_result_field->append("Card type: " + QString::fromStdString(detectCardType(input)));
    }else{
        ui->window2_result_field->append("BAD FUCKING CARD!");
    }

    //!!! FIX !!!ADD BANK HERE!!!!



}

bool window2::checkLuhn(const std::string &input){
    int sum=0;
    bool second=false;
    for(int i=input.length()-1; i>=0; --i){ //starting from the right end
        int d = input[i] - 'a';             //ASCII string to int
        if(second == true)       d=d*2;     //double every second digit
        sum+=d/10;                          //if result of doubling > 10
        sum+=d%10;                          //add two digits of result
        second=!second;                     //alternating bool -- pos check
    }
    return (sum%10 == 0);
}

string window2::detectCardType(string number)
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


