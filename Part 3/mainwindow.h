#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <vector>


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

        //data vectors required for visa
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



        void connectSignalsSlots();
        void readVisaFile(const QString &fileName);
        void readAmexFile(const QString &fileName);
        void readMCFile(const QString &fileName);

        void saveFile(const QString &fileName);
//        void saveAmexFile(const QString &fileName);
//        void saveMCFile(const QString &fileName);

    private slots:
        void openVisaFile();
        void openAmexFile();
        void openMCFile();
        void openSaveFile();
//        void openSaveAmex();
//        void openSaveMC();
};

#endif // MAINWINDOW_H
