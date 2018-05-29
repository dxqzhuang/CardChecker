#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QString fileContents;

    std::string numberInput;
    void connectSignalsSlots();
    bool checkLuhn(const std::string &input);
    void readFromFile(const QString &fileName);
    int search(const QString &name, char type);
    QString binFind(const QString &name, char type);


    std::vector<QString> visaBin;
    std::vector<QString> visaBankName;
    std::vector<QString> visaCardType1;
    std::vector<QString> visaCardType2;
    std::vector<ushort> visaNameSize;
    std::vector<ushort> visaCT1Size;
    std::vector<ushort> visaCT2Size;
    std::vector<QString> amexBin;
    std::vector<QString> amexCardType;
    std::vector<ushort> amexCTSize;
    std::vector<QString> mcBin;
    std::vector<QString> mcBankName;
    std::vector<ushort> mcNameSize;


private slots:
    void checkInput();
    void loadDatabase();

};

#endif // MAINWINDOW_H
