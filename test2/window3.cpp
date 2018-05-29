#include "window3.h"
#include "ui_window3.h"


window3::window3(database& databs, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window3),
    db(databs)
{
    ui->setupUi(this);
    connectSignalsSlots();
    fillBankList("visa");
    srand(time(NULL));
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
    connect(ui->window3_new_entry_btn,SIGNAL(pressed()), this,SLOT(window3_newEntry_btn_pressed()));
    connect(ui->window3_type_field,SIGNAL(currentIndexChanged(const QString&)),
            this,SLOT(window3_type_field_changed(const QString&)));
}

void window3::window3_type_field_changed(const QString& text)
{
    /**
        if card type is amex,
        grey out bankName dropdown menu! amex does NOT have bank names.
      */
    //1. change bank name dropdownlist based on what card type(visa, mc, amex)
    fillBankList(text.toStdString());

    //2. toggle bank name because apparently amex is only issued by american express
    if(text == QString::fromStdString("amex"))
        ui->window3_bank_field->setEnabled(false);
    else
        ui->window3_bank_field->setEnabled(true);
}

void window3::window3_generate_btn_pressed()
{
    packUpEntryRequirement();
    //4. generate data based on vector
    generateData(data,entryRequirements);


//    cout << "how many: " <<entryRequirement["howMany"] << endl;
//    cout << "cardType: " << entryRequirement["cardType"]<< endl;
//    cout << "bankName: " << entryRequirement["bankName"] << endl;

    //5.initiate window 4 with the data generated as parameter
    wind4 = new window4(data);

    //6. show window 4
    wind4->show();

    std::cout << "hello from window3" << std::endl;
}

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
            try
            {
                cout << "j: " << j << endl;
                int binNum, len;
                string bin; //this is the raw result used by findBinNumber; needs to be converted to int binNum
                string cardNum,
                        cardType = entryRequirements[i]["cardType"],
                        bankName = entryRequirements[i]["bankName"];
                map<string, string> entry; //cardNumber, cardType, bankName

                //1. find the perfect bin number
                if(findBinNumber(cardType,bankName,bin))
                    binNum = stoi(bin);
                else
                    throw BIN_NOT_FOUND;

                //cout << "binNum: " << binNum << endl;
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
            }catch(ERRORS e)
            {
                if(e == BIN_NOT_FOUND)
                    cout << "window3 line 131 error: perfect bin could not be found." << endl;
            }

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

    vector<int> num, temp;
    int i=0,j=0;
    for(auto k:bin) num.push_back(k-'0');
    for(;i++<len-7;)
        num.push_back(rand()%10);
    //debugging
    for(int i=0; i<num.size();i++)
        cout << num[i] << " ";
    //
    int criteria = len%2==0 ? 0 : 1;
    for(temp=num,i=num.size();i-->0;)
        if(i%2==criteria && (num[i]*=2)>9)//if it's a two digit number
            num[i] = num[i]/10 + num[i]%10;
    temp.push_back((j=i=accumulate(num.begin(),num.end(),0))%10==0&&(i/10)%2==0?0:10+10*(i/10)-j);
    //cout << "generateCardNum finished(about to return)!! " << endl;
    return accumulate(temp.begin(),temp.end(),string(), [](string a, int b){return a+to_string(b);});
}

bool window3::findBinNumber(string cardType, string bankName, string &bin)
{
    /**
      @brief find the perfect number that matches BOTH the card type AND the bank name
      @example bank of america, visa card ==> 410234
    */

    //if found, automatically set and return true; else return false
    return db.binFind(bankName, cardType, bin);
}

//!!! BAD! mc is not usable because it doesn't have a cardtype
int window3::cardNumLen(string cardType)
{
    /**
      @brief return the correct length that the specified card type should have
      @example visa ==> 16
      @ pre:  param must be one of the following: "visa",  "amex" ,"mc"
      */
    if(cardType == "visa" || cardType == "mastercard")
        return 16;
    else if(cardType == "amex")
        return 15;
}

void window3::window3_newEntry_btn_pressed()
{
    packUpEntryRequirement();
    ui->window3_how_many_field->clear();
}

void window3::packUpEntryRequirement()
{
    map<string,string> entryRequirement;
    int howMany;
    string cardType, bankName;
    //1. collect from input field the following 3 strings:
    // {how many, card type, bank name}
    howMany = std::stoi(ui->window3_how_many_field->text().toStdString());
    cardType = ui->window3_type_field->currentText().toStdString();
    bankName = ui->window3_bank_field->currentText().toStdString();


    //2. push the collected information into a map.
    entryRequirement["howMany"] = std::to_string(howMany);
    entryRequirement["cardType"] = cardType;
    entryRequirement["bankName"] = bankName;
    entryRequirements.push_back(entryRequirement);
}

void window3::fillBankList(const string &cardType)
{
    /*
     * fill/refill bank name dropdown list based on card type
     * because visa/amex/mastercard all have different issuing bank vectors
     */
    QStringList commands;
    //ui->window3_bank_field->addItem();
    if(cardType == "visa")
        for(int i=10; i<db.visaBankName.size();i++)
            commands.push_back(db.visaBankName[i]);
    else if(cardType == "mastercard")
        for(int i=0; i<db.mcBankName.size(); i++)
            commands.push_back(db.mcBankName[i]);
    else if(cardType == "amex")
        commands.push_back(QString::fromStdString("American Express"));
    commands = commands.toSet().toList();
//    if(cardType == "mastercard")
//        for(int i=0; i<37; i++)
//            commands.removeAt(i);

    ui->window3_bank_field->clear();
    ui->window3_bank_field->addItems(commands);
}
