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
    std::string input=numberInput;
    std::cout<<input;

    if(checkLuhn(input)){
        std::cout<<"what";
        std::cout<<input;
//        QDialog::
    }
    else{
        std::cout<<"huh?";
    }
}

bool MainWindow::checkLuhn(const std::string &input){
    int sum=0;
    bool second=false;
    for(int i=input.length()-1; i>=0; --i){     //starting from the right end
        int d = input[i] - 'a';                 //ASCII string to int
        if(second == true)       d=d*2;         //double every second digit
        sum+=d/10;                              //if result of doubling > 10
        sum+=d%10;                              //add two digits of result
        second=!second;                         //alternating bool
    }
    std::cout<<"here";
    return (sum%10 == 0);
}
