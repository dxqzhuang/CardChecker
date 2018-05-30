#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
using namespace std;
#include <QString>
#include <QFile>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QProgressBar>



using namespace std;

enum ERRORS{BIN_NOT_FOUND};
class database
{
public:
    database();
    ~database();
    bool readFromFile(const QString &fileName);
    QString randomCardType(string card);    //return a random card type("Classic", etc)
    bool whichBankIssuedThis(QString card, string& bankName, string&level);

    bool binFind(const string& bankName, const string& cardType, string& bin);




    QProgressBar* progress;
    std::vector<QString> visaBin;
    std::vector<QString> visaBankName;
    std::vector<QString> visaCardType1;
    std::vector<QString> visaCardType2;
    std::vector<QString> visaCountry;
    std::vector<ushort> visaNameSize;
    std::vector<ushort> visaCT1Size;
    std::vector<ushort> visaCT2Size;
    std::vector<ushort> visaCountrySize;
    std::vector<ushort> visaPhoneSize;

    //data vectors required for amex
    std::vector<QString> amexBin;
    std::vector<QString> amexCardType;
    std::vector<ushort> amexCTSize;
    std::vector<ushort> amexPhoneSize;

    //data vectors required for mc
    std::vector<QString> mcBin;
    std::vector<QString> mcBankName;
    std::vector<QString> mcCountry;
    std::vector<ushort> mcNameSize;
    std::vector<ushort> mcCountrySize;
    std::vector<ushort> mcPhoneSize;
    QString fileContents;

    //
    void setProgressBar(QProgressBar* bar);

private:
    int search(const QString &name, char type);
    bool searchVisa(const string &cardType, const string& bankName, string &bin);
    bool searchMc(const string &cardType, const string& bankName, string &bin);
    bool searchAmex(const string &cardType, string&bin);

};

#endif // DATABASE_H
