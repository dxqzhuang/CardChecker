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
    QString line;
    QString subLine;
//    while(!input.atEnd())
//        if(input.getChar(&data))
//            fileContents += data;
    ushort index;
    QChar qdata;
    for(size_t i =0; i<171; ++i){   //read from .bat file
        if(input.getChar(&data)){
            fileContents+=data;
        }
    }


    line=fileContents;
    line.remove(0,113);
//    subLine="";
    QChar temp;
//    while(1){
        //1. reading in BIN
        for(int i=0; i<6; i++){
            subLine+=line[i];
        }
        bin.push_back(subLine);

        line.remove(0,6);   //clear off bin
        subLine = "";       //clearing subline

        //2. read in stringSize for bank name(unicode, 7th digit)
        temp=line[6];
        nameSize.push_back(temp.unicode()); //char to ushort

        //disregard size and 3 null chars
        line.remove(0,4);

        //3. read in bank name//nameSize[j] fix counter later
        for(ushort i=0; i<(temp.unicode()); i++){
            subLine+=line[i];
        }
        bankName.push_back(subLine);

//        line.remove(0,nameSize[0]);       //nameSize is ushort, problem
        subLine = "";   //clearing subline

        //4. read in cardtype
//        QChar type1=line[0];
//        ui->fileContentsDisplay->append(line);


//        switch(type1.toLatin1()){
//            case 'N':
//                cardType1[0].push_back("N/A");
//                line.remove(0,3);
//                break;
//            case 'C':
//                cardType1[0].push_back("CREDIT");
//                line.remove(0,6);
//                break;
//            case 'D':
//                cardType1[0].push_back("DEBIT");
//                line.remove(0,5);
//                break;
//            case 'P':
//                cardType1[0].push_back("PREPAID");
//                line.remove(0,7);
//                break;
//            default:
//                ui->fileContentsDisplay->append("CARDTYPE 1 READ FAILURE");
//                break;
//        }





        //read in card type 1
        //read in card type 2
        //read in country
        //read in junk until first number appears
        //remove all that's is read in line
//    }






    input.close();
//    ui->fileContentsDisplay->clear();
    ui->fileContentsDisplay->append(bin[0]);
    ui->fileContentsDisplay->append(bankName[0]);
//    ui->fileContentsDisplay->append(cardType1[0]);


//    ui->fileContentsDisplay->append(fileContents);
//    ui->fileContentsDisplay->append(qdata);

//    std::cout<<index<<std::endl;

//    ui->fileContentsDisplay->append(" is ASCII position: ");
//    QChar what('');
//    ui->fileContentsDisplay->append(what);
//    QChar thefuck('↕');
//    ui->fileContentsDisplay->append(thefuck);


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
