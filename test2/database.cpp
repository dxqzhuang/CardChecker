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
