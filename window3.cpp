#include "window3.h"
#include "ui_window3.h"

window3::window3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window3)
{
    ui->setupUi(this);
    connectSignalsSlots();
}

window3::~window3()
{
    delete ui;
}

void window3::connectSignalsSlots()
{
//    connect(ui->loadAmex, SIGNAL(pressed()), this, SLOT(openAmexFile()));
//    connect(ui->loadVisa,SIGNAL(pressed()), this,SLOT(openVisaFile()));
//    connect(ui->loadMC,SIGNAL(pressed()), this,SLOT(openMCFile()));
//    connect(ui->saveFileButton,SIGNAL(pressed()), this,SLOT(openSaveFile()));
    connect(ui->window3_generate_btn,SIGNAL(pressed()), this,SLOT(window3_generate_btn_pressed()));

}

void window3::window3_generate_btn_pressed()
{

    int howMany;
    string cardType, bankName;
    vector<map<string,string>>entryRequirements;
    map<string,string> entryRequirement;
    //1. collect from input field the following 3 strings:
    // {how many, card type, bank name}
    howMany = std::stoi(ui->window3_how_many_field->text().toStdString());
    cardType = ui->window3_cardType_field->text().toStdString();
    bankName = ui->window3_bankName_field->text().toStdString();


    //2. push the collected information into a map.
    entryRequirement["howMany"] = std::to_string(howMany);
    entryRequirement["cardType"] = cardType;
    entryRequirement["bankName"] = bankName;

    //3. push the map into vector
    entryRequirements.push_back(entryRequirement);

    //4. generate data based on vector
    generateData(data,entryRequirements);


    cout << "how many: " <<entryRequirement["howMany"] << endl;
    cout << "cardType: " << entryRequirement["cardType"]<< endl;
    cout << "bankName: " << entryRequirement["bankName"] << endl;

    //5.initiate window 4 with the data generated as parameter
    wind4 = new window4(data);

    //6. show window 4
    wind4->show();

    std::cout << "hello from window3" << std::endl;
}

//!!BUG HERE FIX IT!!
void window3::generateData(vector<map<string,string>>& data,
                  vector<map<string,string>>entryRequirements)
{
    /**
      @param n: how many entries to generate
      @param data:
      [ //vector
          { //map
            {"cardNumber","123"},
            {"cardType","gold"},
            {"bankName","BofA"}
          },
          ...
      ]

      @param entry requirements:
      [ //vector
          { //map
            {"howMany","12"},
            {"cardType","gold"},
            {"bankName","BofA"}
          },
          ...
      ]
      */


    for(int i=0; i<entryRequirements.size();i++)
    {
        cout << "i: " << i << endl;
        for(int j=0; j<std::stoi(entryRequirements[i]["howMany"]);j++)
        {
            cout << "j: " << j << endl;
            int binNum, len;
            string cardNum,
                    cardType = entryRequirements[i]["cardType"],
                    bankName = entryRequirements[i]["bankName"];
            map<string, string> entry; //cardNumber, cardType, bankName

            //1. find the perfect bin number
            binNum = std::stoi(findBinNumber(cardType, bankName)); //FINISH THIS!!!!

            cout << "binNum: " << binNum << endl;
            //2. find the correct length that this card type should have
            len = cardNumLen(cardType);

            //3. generate the card number
            cardNum = generateCardNum(std::to_string(binNum),len);


            //4. push the generated card number, card type, and bank name into entry map
            entry["cardNumber"] = cardNum;
            entry["cardType"] = cardType;
            entry["bankName"] = bankName;
            //cout << "entry[cardNum]: " << entry[cardNum] << endl;
            //5. push map into data vector
            data.push_back(entry);
        }
    }
}

string window3::generateCardNum(string bin, int len)
{
    /**
     * @brief generate credit card number based on first 6 digits and required length
     * @param len: length of card number(including bin and checkdigit)
     * @note check sum explained at https://www.sapling.com/7966257/checksum-credit-card
     */
    //cout << "generateCardNum fired!! bin:  " << bin << "; len: " << len << endl;
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
    //cout << "generateCardNum finished(about to return)!! " << endl;
    return accumulate(temp.begin(),temp.end(),string(), [](string a, int b){return a+to_string(b);});
}

string window3::findBinNumber(string cardType, string bankName)
{
    /**
      @brief find the perfect number that matches BOTH the card type AND the bank name
      @example bank of america, visa card ==> 410234
      */
    //!!! THIS IS A STUB!!FIX THIS!!@
    return "400109";
}

int window3::cardNumLen(string cardType)
{
    /**
      @brief return the correct length that the specified card type should have
      @example visa ==> 16
      @ pre:  param must be one of the following: "visa",  "amex" ,"mc"
      */
    if(cardType == "visa" || cardType == "mc")
        return 16;
    else if(cardType == "amex")
        return 15;
}
