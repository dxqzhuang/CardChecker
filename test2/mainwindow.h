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

        std::vector<QString> bin;
        std::vector<QString> bankName;
        std::vector<QString> cardType1;
        std::vector<QString> cardType2;
        std::vector<QString> country;
        std::vector<ushort> nameSize;

        std::vector<ushort> CT1Size;
        std::vector<ushort> CT2Size;
        std::vector<ushort> countrySize;
        std::vector<ushort> phoneSize;

        std::vector<QString> amexBin;
        std::vector<QString> amexBankName;
        std::vector<QString> amexCardType;
//        std::vector<ushort> amexNameSize;
        std::vector<ushort> amexCTSize;
        std::vector<ushort> amexPhoneSize;




        void connectSignalsSlots();
        void readVisaFile(const QString &fileName);
        void readAmexFile(const QString &fileName);
        void saveFile(const QString &fileName);

    private slots:
        void openVisaFile();
        void openAmexFile();
        void openSaveFile();
};

#endif // MAINWINDOW_H
