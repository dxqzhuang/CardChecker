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
//    connect(ui->loadAmex, SIGNAL(pressed()), this, SLOT(openAmexFile()));
//    connect(ui->loadVisa,SIGNAL(pressed()), this,SLOT(openVisaFile()));
//    connect(ui->loadMC,SIGNAL(pressed()), this,SLOT(openMCFile()));
//    connect(ui->saveFileButton,SIGNAL(pressed()), this,SLOT(openSaveFile()));
    connect(ui->window1_check_btn,SIGNAL(pressed()), this,SLOT(window1_check_btn_pressed()));
    connect(ui->window1_generate_btn,SIGNAL(pressed()), this,SLOT(window1_generate_btn_pressed()));

}


void MainWindow::window1_check_btn_pressed()
{

    std::cout << "hello" << std::endl;
    wind2 = new window2();
    wind2->show();
}


void MainWindow::window1_generate_btn_pressed()
{
    std::cout << "hello" << std::endl;
    wind3 = new window3();
    wind3->show();
}






//void MainWindow::readVisaFile(const QString &fileName)
//{
//    char data;
//    QFile input(fileName);
//    input.open(QFile::ReadOnly);
//    fileContents.clear();
//    QString line;                       //to be manipulated by the function

//    while(!input.atEnd()){              //read from .bat file
//        if(input.getChar(&data)){
//            fileContents+=data;
//        }
//    }

//    fileContents.remove(0,107);

//    size_t entry=0;
//    while(entry<1000){                  //total entries: 35154
//        fileContents.remove(0,2);       //clean up 06 and 04
//                                        //assuming 06 is bin size
//                                        //unsure what 04 means
//                                        //however sizevector not necessary
//        //0. reading in size info
//        visaCT1Size.push_back(fileContents[0].unicode());
//        visaCT2Size.push_back(fileContents[1].unicode());
//        visaCountrySize.push_back(fileContents[2].unicode());
//        visaPhoneSize.push_back(fileContents[3].unicode());
//        fileContents.remove(0,4);

//        //1. reading in BIN
//        for(int i=0; i<6; i++){
//            line+=fileContents[i];
//        }
//        visaBin.push_back(line);
//        fileContents.remove(0,6);   //clean up
//        line = "";

//        //2. read in stringSize for bank name(unicode, 7th digit)
//        visaNameSize.push_back(fileContents[0].unicode()); //char to ushort

//        //disregard size and 3 null chars
//        fileContents.remove(0,4);   //clean up

//        //3. read in bank name//nameSize[j] fix counter later
//        for(ushort i=0; i<(visaNameSize[entry]); ++i){
//            line+=fileContents[i];
//        }
//        visaBankName.push_back(line);

//        fileContents.remove(0,int(visaNameSize[entry]));    //clean up
//        line = "";

//        //4. read in cardtype1
//        for(ushort i=0; i<visaCT1Size[entry];++i){
//            line+=fileContents[i];
//        }
//        visaCardType1.push_back(line);

//        fileContents.remove(0,int(visaCT1Size[entry]));    //clean up
//        line = "";

//        //5. read in cardtype2
//        for(ushort i=0; i<visaCT2Size[entry];++i){
//            line+=line[i];
//        }
//        visaCardType2.push_back(line);
//        fileContents.remove(0,int(visaCT2Size[entry]));    //clean up
//        line = "";

//        //6.read in country
//        for(ushort i=0; i<visaCountrySize[entry];++i){
//            line+=fileContents[i];
//        }
//        visaCountry.push_back(line);

//        fileContents.remove(0,int(visaCountrySize[entry]));    //clean up
//        line = "";
//        //remove junk
//        fileContents.remove(0,int(visaPhoneSize[entry]));  //clean up phone numbers
//        ui->fileContentsDisplay->append(visaBankName[entry]);
//        entry++;
//    }
//    input.close();
//}

//void MainWindow::readAmexFile(const QString &fileName)
//{
//    char data;
//    QFile input(fileName);
//    input.open(QFile::ReadOnly);
//    fileContents.clear();
//    QString line;                       //to be manipulated by the function

//    while(!input.atEnd()){              //read from .bat file
//        if(input.getChar(&data)){
//            fileContents+=data;
//        }
//    }

//    fileContents.remove(0,84);

//    size_t entry=0;
//    while(entry<1215){                  //total entries: 1215
//        fileContents.remove(0,3);       //clean up bin size and country size
//                                        //and bank name size
//        //0. reading in size info
//        amexCTSize.push_back(fileContents[0].unicode());
//        amexPhoneSize.push_back(fileContents[1].unicode());
//        fileContents.remove(0,2);

//        //1. reading in BIN
//        for(int i=0; i<6; i++){
//            line+=fileContents[i];
//        }
//        amexBin.push_back(line);
//        fileContents.remove(0,6);   //clean up
//        line = "";


//        //2. remove country
//        fileContents.remove(0,24);    //clean up

//        //3.remove N/A bank names
//        fileContents.remove(0,3);

//        //4. read in cardtypes
//        for(ushort i=0; i<amexCTSize[entry];++i){
//            line+=fileContents[i];
//        }
//        amexCardType.push_back(line);

//        fileContents.remove(0,int(amexCTSize[entry]));    //clean up
//        line = "";

//        //5. remove phone number
//        fileContents.remove(0,int(amexPhoneSize[entry]));  //clean up phone numbers
//        entry++;
//    }
//    input.close();
//}

//void MainWindow::readMCFile(const QString &fileName)
//{
//    char data;
//    QFile input(fileName);
//    input.open(QFile::ReadOnly);
//    fileContents.clear();
//    QString line;                       //to be manipulated by the function

//    while(!input.atEnd()){              //read from .bat file
//        if(input.getChar(&data)){
//            fileContents+=data;
//        }
//    }

//    fileContents.remove(0,79);

//    size_t entry=0;
//    while(entry<500){                  //total entries: ???
//        fileContents.remove(0,2);       //clean up 06 and 04
//                                        //assuming 06 is bin size
//                                        //unsure what 04 means
//                                        //however sizevector not necessary
//        //0. reading in size info
//        mcCountrySize.push_back(fileContents[0].unicode());
//        mcPhoneSize.push_back(fileContents[1].unicode());
//        fileContents.remove(0,2);

//        //1. reading in BIN
//        for(int i=0; i<6; i++){
//            line+=fileContents[i];
//        }
//        mcBin.push_back(line);
//        fileContents.remove(0,6);   //clean up
//        line = "";

//        //2. read in stringSize for bank name(unicode, 7th digit)
//        mcNameSize.push_back(fileContents[0].unicode()); //char to ushort

//        //disregard size and 3 null chars
//        fileContents.remove(0,4);   //clean up

//        //3. read in bank name//nameSize[j] fix counter later
//        for(ushort i=0; i<(mcNameSize[entry]); ++i){
//            line+=fileContents[i];
//        }
//        mcBankName.push_back(line);

//        fileContents.remove(0,int(mcNameSize[entry]));    //clean up
//        line = "";


//        //6.read in country
//        for(ushort i=0; i<mcCountrySize[entry];++i){
//            line+=fileContents[i];
//        }
//        mcCountry.push_back(line);

//        fileContents.remove(0,int(mcCountrySize[entry]));    //clean up
//        line = "";
//        //remove junk
//        fileContents.remove(0,int(mcPhoneSize[entry]));  //clean up phone numbers
//        ui->fileContentsDisplay->append(mcCountry[entry]);
//        entry++;
//    }
//    input.close();
//}




//void MainWindow::openSaveFile()
//{
//    QString fileName = QFileDialog::getSaveFileName(NULL, "Save File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
//    if(fileName.isNull())
//        return;
//    if(QFileInfo(fileName).suffix().isEmpty())
//      fileName.append(".dat");
//    saveFile(fileName);
//}

//void MainWindow::saveFile(const QString &fileName)
//{
//    QFile output(fileName);
//    output.open(QFile::WriteOnly);
//    output.write(fileContents.toStdString().c_str(), fileContents.size());
//    output.close();
//}

//void MainWindow::openVisaFile()
//{
//    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
//    if(fileName.isNull())
//        return;
//    if(QFileInfo(fileName).suffix().isEmpty())
//      fileName.append(".dat");
//    ui->fileName->setText(fileName);
//    readVisaFile(fileName);
//}

//void MainWindow::openAmexFile(){
//    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
//    if(fileName.isNull())
//        return;
//    if(QFileInfo(fileName).suffix().isEmpty())
//      fileName.append(".dat");
//    ui->fileName->setText(fileName);
//    readAmexFile(fileName);
//}

//void MainWindow::openMCFile(){
//    QString fileName = QFileDialog::getOpenFileName(NULL, "Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
//    if(fileName.isNull())
//        return;
//    if(QFileInfo(fileName).suffix().isEmpty())
//      fileName.append(".dat");
//    ui->fileName->setText(fileName);
//    readMCFile(fileName);
//}

//void MainWindow::changeEvent(QEvent *e)
//{
//    QMainWindow::changeEvent(e);
//    switch (e->type()) {
//    case QEvent::LanguageChange:
//        ui->retranslateUi(this);
//        break;
//    default:
//        break;
//    }
//}
