#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <window2.h>
#include <window3.h>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <vector>
#include <database.h>

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
        //void changeEvent(QEvent *e);


    private:
        Ui::MainWindow *ui;
        window2 *wind2;
        window3 *wind3;
        database db;


        void connectSignalsSlots();

//        void readVisaFile(const QString &fileName);
//        void readAmexFile(const QString &fileName);
//        void readMCFile(const QString &fileName);
//        void saveFile(const QString &fileName);

    private slots:
//        void openVisaFile();
//        void openAmexFile();
//        void openMCFile();
//        void openSaveFile();
        void window1_check_btn_pressed();


        void window1_generate_btn_pressed();
        void loadDatabase();


};

#endif // MAINWINDOW_H
