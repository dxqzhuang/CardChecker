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
