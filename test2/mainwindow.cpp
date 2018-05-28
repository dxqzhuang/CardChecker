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
    connect(ui->saveFileButton,SIGNAL(pressed()), this,SLOT(openSaveFile()));
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
    while(entry<1000){                  //total entries: 35154
        fileContents.remove(0,2);       //clean up 06 and 04
                                        //assuming 06 is bin size
                                        //unsure what 04 means
                                        //however sizevector not necessary
        //0. reading in size info
        CT1Size.push_back(fileContents[0].unicode());
        CT2Size.push_back(fileContents[1].unicode());
        countrySize.push_back(fileContents[2].unicode());
        phoneSize.push_back(fileContents[3].unicode());
        fileContents.remove(0,4);

        //1. reading in BIN
        for(int i=0; i<6; i++){
            line+=fileContents[i];
        }
        bin.push_back(line);
        fileContents.remove(0,6);   //clean up
        line = "";

        //2. read in stringSize for bank name(unicode, 7th digit)
        nameSize.push_back(fileContents[0].unicode()); //char to ushort

        //disregard size and 3 null chars
        fileContents.remove(0,4);   //clean up

        //3. read in bank name//nameSize[j] fix counter later
        for(ushort i=0; i<(nameSize[entry]); ++i){
            line+=fileContents[i];
        }
        bankName.push_back(line);

        fileContents.remove(0,int(nameSize[entry]));    //clean up
        line = "";

        //4. read in cardtype1
        for(ushort i=0; i<CT1Size[entry];++i){
            line+=fileContents[i];
        }
        cardType1.push_back(line);

        fileContents.remove(0,int(CT1Size[entry]));    //clean up
        line = "";

        //5. read in cardtype2
        for(ushort i=0; i<CT2Size[entry];++i){
            line+=line[i];
        }
        cardType2.push_back(line);
        fileContents.remove(0,int(CT2Size[entry]));    //clean up
        line = "";

        //6.read in country
        for(ushort i=0; i<countrySize[entry];++i){
            line+=fileContents[i];
        }
        country.push_back(line);

        fileContents.remove(0,int(countrySize[entry]));    //clean up
        line = "";
        //remove junk
        fileContents.remove(0,int(phoneSize[entry]));  //clean up phone numbers
        ui->fileContentsDisplay->append(bankName[entry]);
        entry++;
    }
    input.close();
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
    output.write(fileContents.toStdString().c_str(), fileContents.size());
    output.close();
}

void MainWindow::openVisaFile()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".dat");
    ui->fileName->setText(fileName);
    readVisaFile(fileName);
}

void MainWindow::openAmexFile(){
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".dat");
    ui->fileName->setText(fileName);
    readAmexFile(fileName);
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
