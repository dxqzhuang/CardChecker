#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSignalsSlots();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectSignalsSlots()
{
    connect(ui->loadAmex, SIGNAL(pressed()), this, SLOT(openAmexFile()));
    connect(ui->loadVisa,SIGNAL(pressed()), this,SLOT(openVisaFile()));
    connect(ui->loadMC,SIGNAL(pressed()), this,SLOT(openMCFile()));
    connect(ui->saveButton,SIGNAL(pressed()), this,SLOT(openSaveFile()));
//    connect(ui->saveAmexButton,SIGNAL(pressed()), this,SLOT(openSaveAmex()));
//    connect(ui->saveMCButton,SIGNAL(pressed()), this,SLOT(openSaveMC()));
}


void MainWindow::readVisaFile(const QString &fileName)
{
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

    fileContents.remove(0,107);

    size_t entry=0;
    while(entry<35154){                  //total entries: 35154
        fileContents.remove(0,2);       //clean up 06 and 04
                                        //assuming 06 is bin size
                                        //unsure what 04 means
                                        //however sizevector not necessary
        //0. reading in size info
        visaCT1Size.push_back(fileContents[0].unicode());
        visaCT2Size.push_back(fileContents[1].unicode());
        visaCountrySize.push_back(fileContents[2].unicode());
        visaPhoneSize.push_back(fileContents[3].unicode());
        fileContents.remove(0,4);

        //1. reading in BIN
        for(int i=0; i<6; i++){
            line+=fileContents[i];
        }
        visaBin.push_back(line);
        fileContents.remove(0,6);   //clean up
        line = "";

        //2. read in stringSize for bank name(unicode, 7th digit)
        visaNameSize.push_back(fileContents[0].unicode()); //char to ushort

        //disregard size and 3 null chars
        fileContents.remove(0,4);   //clean up

        //3. read in bank name//nameSize[j] fix counter later
        for(ushort i=0; i<(visaNameSize[entry]); ++i){
            line+=fileContents[i];
        }
        visaBankName.push_back(line);

        fileContents.remove(0,int(visaNameSize[entry]));    //clean up
        line = "";

        //4. read in cardtype1
        for(ushort i=0; i<visaCT1Size[entry];++i){
            line+=fileContents[i];
        }
        visaCardType1.push_back(line);

        fileContents.remove(0,int(visaCT1Size[entry]));    //clean up
        line = "";

        //5. read in cardtype2
        for(ushort i=0; i<visaCT2Size[entry];++i){
            line+=fileContents[i];
        }
        visaCardType2.push_back(line);
        fileContents.remove(0,int(visaCT2Size[entry]));    //clean up
        line = "";

        //6.read in country
        for(ushort i=0; i<visaCountrySize[entry];++i){
            line+=fileContents[i];
        }
        visaCountry.push_back(line);

        fileContents.remove(0,int(visaCountrySize[entry]));    //clean up
        line = "";
        //remove junk
        fileContents.remove(0,int(visaPhoneSize[entry]));  //clean up phone numbers
        entry++;
//        ui->fileContentsDisplay->append(visaCardType2[entry]);
    }
    input.close();
    ui->fileContentsDisplay->append("Visa Parsed.");
}

void MainWindow::readAmexFile(const QString &fileName)
{
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

    fileContents.remove(0,84);

    size_t entry=0;
    while(entry<1215){                  //total entries: 1215
        fileContents.remove(0,3);       //clean up bin size and country size
                                        //and bank name size
        //0. reading in size info
        amexCTSize.push_back(fileContents[0].unicode());
        amexPhoneSize.push_back(fileContents[1].unicode());
        fileContents.remove(0,2);

        //1. reading in BIN
        for(int i=0; i<6; i++){
            line+=fileContents[i];
        }
        amexBin.push_back(line);
        fileContents.remove(0,6);   //clean up
        line = "";


        //2. remove country
        fileContents.remove(0,24);    //clean up

        //3.remove N/A bank names
        fileContents.remove(0,3);

        //4. read in cardtypes
        for(ushort i=0; i<amexCTSize[entry];++i){
            line+=fileContents[i];
        }
        amexCardType.push_back(line);

        fileContents.remove(0,int(amexCTSize[entry]));    //clean up
        line = "";

        //5. remove phone number
        fileContents.remove(0,int(amexPhoneSize[entry]));  //clean up phone numbers
        entry++;
    }
    input.close();
    ui->fileContentsDisplay->append("AMEX Parsed.");
}

void MainWindow::readMCFile(const QString &fileName)
{
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

    fileContents.remove(0,79);

    size_t entry=0;
    while(entry<17297){                  //total entries: 17297
        fileContents.remove(0,2);       //clean up 06 and 04
                                        //assuming 06 is bin size
                                        //unsure what 04 means
                                        //however sizevector not necessary
        //0. reading in size info
        mcCountrySize.push_back(fileContents[0].unicode());
        mcPhoneSize.push_back(fileContents[1].unicode());
        fileContents.remove(0,2);

        //1. reading in BIN
        for(int i=0; i<6; i++){
            line+=fileContents[i];
        }
        mcBin.push_back(line);
        fileContents.remove(0,6);   //clean up
        line = "";

        //2. read in stringSize for bank name(unicode, 7th digit)
        mcNameSize.push_back(fileContents[0].unicode()); //char to ushort

        //disregard size and 3 null chars
        fileContents.remove(0,4);   //clean up

        //3. read in bank name//nameSize[j] fix counter later
        for(ushort i=0; i<(mcNameSize[entry]); ++i){
            line+=fileContents[i];
        }
        mcBankName.push_back(line);

        fileContents.remove(0,int(mcNameSize[entry]));    //clean up
        line = "";


        //6.read in country
        for(ushort i=0; i<mcCountrySize[entry];++i){
            line+=fileContents[i];
        }
        mcCountry.push_back(line);

        fileContents.remove(0,int(mcCountrySize[entry]));    //clean up
        line = "";
        //remove junk
        fileContents.remove(0,int(mcPhoneSize[entry]));  //clean up phone numbers
//        ui->fileContentsDisplay->append(mcBankName[entry]);
        entry++;
    }
    input.close();
    ui->fileContentsDisplay->append("MC Parsed.");
}

void MainWindow::openSaveFile()
{
    QString fileName = QFileDialog::getSaveFileName(NULL, "Save File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".dat");
    saveFile(fileName);
}

void MainWindow::saveFile(const QString &fileName)
{
    QFile output(fileName);
    output.open(QFile::WriteOnly);
    QString str;

    for(size_t i=0; i<amexBin.size();i++){
        output.write("A",1);                        //AMEX
        str=amexCTSize[i];                          //Size info
        output.write(str.toStdString().c_str(),1);

        output.write(amexBin[i].toStdString().c_str(), 6);
//        output.write(" ",1);
        output.write(amexCardType[i].toStdString().c_str(),amexCTSize[i]);
        output.write("\n",1);
    }

    for(size_t i=0; i<visaBin.size();i++){
        output.write("V",1);                        //VISA
        str=visaNameSize[i];                        //Size info
        output.write(str.toStdString().c_str(),1);
        str=visaCT1Size[i];
        output.write(str.toStdString().c_str(),1);
        str=visaCT2Size[i];
        output.write(str.toStdString().c_str(),1);

        output.write(visaBin[i].toStdString().c_str(), 6);  //Card info
//        output.write(" ",1);
        output.write(visaBankName[i].toStdString().c_str(),visaNameSize[i]);
//        output.write(" ",1);
        output.write(visaCardType1[i].toStdString().c_str(),visaCT1Size[i]);
//        output.write(" ",1);
        output.write(visaCardType2[i].toStdString().c_str(),visaCT2Size[i]);
//        output.write(" ",1);
//        output.write(visaCountry[i].toStdString().c_str(),visaCountrySize[i]);
        output.write("\n",1);
    }

    for(size_t i=0; i<mcBin.size();i++){        //master cards
        output.write("M",1);
        str=mcNameSize[i];
        output.write(str.toStdString().c_str(),1);

        output.write(mcBin[i].toStdString().c_str(), 6);
//        output.write(" ",1);
        output.write(mcBankName[i].toStdString().c_str(),mcNameSize[i]);
//        output.write(" ",1);
//        output.write(mcCountry[i].toStdString().c_str(),mcCountrySize[i]);
        output.write("\n",1);
    }
    output.close();
}

void MainWindow::openVisaFile()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".dat");
    readVisaFile(fileName);
}

void MainWindow::openAmexFile(){
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".dat");
    readAmexFile(fileName);
}

void MainWindow::openMCFile(){
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".dat");
    readMCFile(fileName);
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