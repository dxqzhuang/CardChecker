#include "database.h"

database::database()
{
    srand(time(NULL));
}


void database::readFromFile(const QString &fileName){
    char data;
    QFile input(fileName);
    input.open(QFile::ReadOnly);
    fileContents.clear();
    QString line;                       //to be manipulated by the function

    while(!input.atEnd()){              //read from .bat file
        if(input.getChar(&data)){
            fileContents+=data;
        }
    }

    size_t entry=0, amex=0, mc=0, visa=0;
    QChar type;
    while(entry<53666){                  //total entries: 53666
        //0. reading in type
        type=fileContents[0];
        switch(type.toLatin1()){
        case 'A':
            amexCTSize.push_back(fileContents[1].unicode());  //read in CT size
            fileContents.remove(0,2);               //clean up
            for(int i=0;i<6;++i){                //read in BIN
                line+=fileContents[i];
            }
            amexBin.push_back(line);                //clean up
            fileContents.remove(0,6);
            line="";
            for(ushort i=0;i<amexCTSize[amex];++i){    //read in cardtype
                line+=fileContents[i];
            }
            amexCardType.push_back(line);
            fileContents.remove(0, amexCTSize[amex]+1);//clean up +1 of \n
            line="";
//            ui->outputField->append("Just read in an Amex");
            amex++;     //counter for amexCTSize vector
            break;
        case 'M':
            mcNameSize.push_back(fileContents[1].unicode());  //read in CT size
            fileContents.remove(0,2);               //clean up
            for(int i=0;i<6;++i){                //read in BIN
                line+=fileContents[i];
            }
            mcBin.push_back(line);                  //clean up
            fileContents.remove(0,6);
            line="";
            for(ushort i=0;i<mcNameSize[mc];++i){
                line+=fileContents[i];
            }
            mcBankName.push_back(line);             //read in bank name
            fileContents.remove(0,mcNameSize[mc]+1);
            line="";
//            ui->outputField->append("Just read in an MC");
            mc++;
            break;
        case 'V':
            //banknamesize, CT1 size, CT2 size, bin, bank name, CT1, CT2 , \n;
            visaNameSize.push_back(fileContents[1].unicode());
            visaCT1Size.push_back(fileContents[2].unicode());
            visaCT2Size.push_back(fileContents[3].unicode());
            fileContents.remove(0,4);

            for(int i=0; i<6; i++){
                line+=fileContents[i];
            }
            visaBin.push_back(line);    //read in BIN
            fileContents.remove(0,6);   //clean up
            line = "";

            for(ushort i=0; i<(visaNameSize[visa]); ++i){
                line+=fileContents[i];
            }
            visaBankName.push_back(line);             //read in bank name
            fileContents.remove(0,int(visaNameSize[visa]));    //clean up
            line = "";

            for(ushort i=0; i<(visaCT1Size[visa]); ++i){
                line+=fileContents[i];
            }
            visaCardType1.push_back(line);             //read in CT1
            fileContents.remove(0,int(visaCT1Size[visa]));    //clean up
            line = "";

            for(ushort i=0; i<(visaCT2Size[visa]); ++i){
                line+=fileContents[i];
            }
            visaCardType2.push_back(line);             //read in CT2
            fileContents.remove(0,int(visaCT2Size[visa])+1);    //clean up
            line = "";
//            ui->outputField->append("Just read in an VISA");

            visa++;
            break;
        default:
            break;
            //ui->outputField->append("Error reading in type.");
        }
        entry++;
    }
    input.close();
}

QString database::randomCardType(string card)
{
    //card: visa/mc/amex
    if(card == "visa")
        return visaCardType2[rand()%visaCardType2.size()];
//    else if(card == "mc")
//        return mcCar[rand()%visaCardType2.size()];
    else if(card == "amex")
        return amexCardType[rand()%amexCardType.size()];
    else
        cout << "ERROR: randomCardType: bad type!" << endl;
}

bool database::whichBankIssuedThis(QString card, string &bankName, string &level)
{
    /**
      @brief find the bank that issued the given card number, and find the index
      */
    //1. pull out the 6 digit bin number
    QString bin = card.mid(0,6);
    std::vector<QString>::iterator it;
    int index;

    //2. search the bin from visaBin, amex, and mcBin
    it = std::find(visaBin.begin(), visaBin.end(), bin);
    if(it!= visaBin.end()){
        index =std::distance(visaBin.begin(), it);
        level = visaCardType2[index].toStdString();
        bankName = visaBankName[index].toStdString();
        return true;
    }

    it = std::find(mcBin.begin(), mcBin.end(), bin);
    if(it!= mcBin.end()){
        index =std::distance(mcBin.begin(), it);
        level = "N/A";
        bankName = mcBankName[index].toStdString();
        return true;
    }

    it = std::find(amexBin.begin(), amexBin.end(), bin);
    if(it!= amexBin.end()){
        index =std::distance(amexBin.begin(), it);
        level = amexCardType[index].toStdString();
        bankName = "American Express";
        return true;
    }

    //3. if bin is not found:
    return false;
}

bool database::binFind(const string& bankName, const string& cardType, string& bin)
{
    /**
      given a bank name and a card type, return a perfect bin number that satisfies both requirements
    @param cardType: visa/mc/amex
    @paran bankName: "bank of america", etc...
    @param bin this will be set to the found bin if bin is found.
      */

    //if not found in visa vectors ,
    //see if it can be found in mastercard vectors; if not,
    //see if it can be found in amex vectors
    return searchVisa(cardType,bankName,bin) ||
            searchMc(cardType,bankName,bin) ||
            searchAmex(cardType, bin);

}

bool database::searchVisa(const string& cardType, const string& bankName, string& bin)
{
    /***
     * in visaBankNames vector, search for the given bank name
     * helper function for binFind
     */
    if(cardType != "visa") return false;

    std::vector<QString>::iterator it;
    int index;

    it = std::find(visaBankName.begin(), visaBankName.end(), QString::fromStdString(bankName));
    if(it!= visaBankName.end()){
        index =std::distance(visaBankName.begin(), it);
        bin = visaBin[index].toStdString();
        return true;
    }

    return false;

}

bool database::searchMc(const string &cardType, const string& bankName, string &bin)
{
    /***
     * in mcBankNames vector, search for the given bank name
     * helper function for binFind
     */
    if(cardType != "mastercard") return false;

    std::vector<QString>::iterator it;
    int index;

    it = std::find(mcBankName.begin(), mcBankName.end(), QString::fromStdString(bankName));
    if(it!= mcBankName.end()){
        index =std::distance(mcBankName.begin(), it);
        bin = mcBin[index].toStdString();
        return true;
    }

    return false;
}

bool database::searchAmex(const string& cardType, string&bin)
{
    /**
      since bank names are all N/A with amex, just return a random bin in amexBin vector
      */
    if(cardType != "amex") return false;
    bin = amexBin[rand()%amexBin.size()].toStdString();
    return true;
}

