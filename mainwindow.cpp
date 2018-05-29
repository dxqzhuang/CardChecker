#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    connect(ui->checkButton,SIGNAL(pressed()), this,SLOT(checkInput()));
    connect(ui->loadButton,SIGNAL(pressed()), this, SLOT(loadDatabase()));
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

void MainWindow::checkInput(){
    std::string input=ui->inputField->text().toUtf8().constData();

    if(checkLuhn(input)){
        ui->outputField->setText("Luhn check: PASS");
    }
    else{
        ui->outputField->setText("Luhn check: FAIL");
    }
}

bool MainWindow::checkLuhn(const std::string &input){
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

void MainWindow::loadDatabase()
{
    QString fileName=QFileDialog::getOpenFileName(NULL,"Source File","/Users/pjw/Dropbox/CS 3A/2018/Mars" , "*.dat");
    if(fileName.isNull())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
       fileName.append(".dat");
    readFromFile(fileName);
}

void MainWindow::readFromFile(const QString &fileName){
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
            for(size_t i=0;i<6;++i){                //read in BIN
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
            for(size_t i=0;i<6;++i){                //read in BIN
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
            ui->outputField->append("Error reading in type.");
        }
        entry++;
    }
    input.close();
    ui->outputField->append("Data reading complete.");

    //following is debugg output, delete when done testing
    ui->outputField->append("Looking for CLASSIC in visa.dat");
    QString str=binFind("CLASSIC", 'c');
    ui->outputField->append(str);
}

int MainWindow::search(const QString &name, char type){
    //only searches visa files so far
    std::vector<QString>::iterator index;
    int it=0;

    switch(type){
    case 'c':
        index = std::find(visaCardType2.begin(), visaCardType2.end(), name);
        if(index!= visaCardType2.end()){
            it=std::distance(visaCardType2.begin(), index);
        }
        break;
    case 'b':
        index = std::find(visaBankName.begin(), visaBankName.end(), name);
        if(index!= visaBankName.end()){
            it=std::distance(visaBankName.begin(), index);
        }
        break;
    default:
        ui->outputField->append("Search error.");
    }
    return it;
}

QString MainWindow::binFind(const QString &name, char type){
    //returns a bin with given requirement
    int index=search(name,type);
    return visaBin[index];
}
