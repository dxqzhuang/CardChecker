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
        std::vector<ushort> nameSize; //bankName string size
        std::vector<QString> bankName;
        std::vector<QString> cardType1;
        std::vector<QString> cardType2;
        std::vector<QString> country;



        void connectSignalsSlots();
        void readFile(const QString &fileName);
        void saveFile(const QString &fileName);

    private slots:
        void openInputFile();
        void openSaveFile();
};

#endif // MAINWINDOW_H
