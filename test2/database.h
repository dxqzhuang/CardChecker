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
using namespace std;
class database
{
public:

    database();
    void readFromFile(const QString &fileName);
    QString randomCardType(string card);
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
};

#endif // DATABASE_H
