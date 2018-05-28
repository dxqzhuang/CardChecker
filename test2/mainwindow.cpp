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
    connect(ui->exitButton, SIGNAL(pressed()), this, SLOT(close()));
    connect(ui->openFileButton,SIGNAL(pressed()), this,SLOT(openInputFile()));
    connect(ui->saveFileButton,SIGNAL(pressed()), this,SLOT(openSaveFile()));
}


void MainWindow::readFile(const QString &fileName)
{
    char data;
    QFile input(fileName);
    input.open(QFile::ReadOnly);
    fileContents.clear();
    QString line;       //to be manipulated by the function
    QString subLine;    //to be used for push_back vectors
//    while(!input.atEnd())
//        if(input.getChar(&data))
//            fileContents += data;
    ushort index;
    QChar qdata;
    for(size_t i =0; i<178; ++i){   //read from .bat file
        if(input.getChar(&data)){
            fileContents+=data;
        }
    }


    line=fileContents;
    line.remove(0,109);
    subLine="";
    QChar temp;
//    while(1){

    //0. reading in size info
    CT1Size.push_back(line[0].unicode());
    CT2Size.push_back(line[1].unicode());
    countrySize.push_back(line[2].unicode());
    phoneSize.push_back(line[3].unicode());
    line.remove(0,4);

    //1. reading in BIN
    for(int i=0; i<6; i++){
        subLine+=line[i];
    }
    bin.push_back(subLine);
    line.remove(0,6);   //clean up
    subLine = "";       //clearing subline

    //2. read in stringSize for bank name(unicode, 7th digit)
    nameSize.push_back(line[0].unicode()); //char to ushort

    //disregard size and 3 null chars
    line.remove(0,4);   //clean up

    //3. read in bank name//nameSize[j] fix counter later
    for(ushort i=0; i<(nameSize[0]); ++i){
        subLine+=line[i];
    }
    bankName.push_back(subLine);

    line.remove(0,int(nameSize[0]));    //clean up
    subLine = "";

    //4. read in cardtype1
    for(ushort i=0; i<CT1Size[0];++i){
        subLine+=line[i];
    }
    cardType1.push_back(subLine);

    line.remove(0,int(CT1Size[0]));    //clean up
    subLine = "";

    //5. read in cardtype2
    for(ushort i=0; i<CT2Size[0];++i){
        subLine+=line[i];
    }
    cardType2.push_back(subLine);
    line.remove(0,int(CT2Size[0]));    //clean up
    subLine = "";
    //6.read in country
    for(ushort i=0; i<countrySize[0];++i){
        subLine+=line[i];
    }
    country.push_back(subLine);
    line.remove(0,int(countrySize[0]));    //clean up
    subLine = "";
    //remove junk
    line.remove(0,int(phoneSize[0]));    //clean up phone numbers

//    }






    input.close();
//    ui->fileContentsDisplay->clear();
    ui->fileContentsDisplay->append(bin[0]);
    ui->fileContentsDisplay->append(bankName[0]);
    ui->fileContentsDisplay->append(cardType1[0]);
    ui->fileContentsDisplay->append(cardType2[0]);
    ui->fileContentsDisplay->append(country[0]);
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

void MainWindow::openInputFile()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".dat");
    ui->fileName->setText(fileName);
    readFile(fileName);
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
