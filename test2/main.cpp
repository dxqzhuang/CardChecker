#include "mainwindow.h"
#include <QApplication>
#include <QTextDocument>
#include <QPainter>
#include <QtPrintSupport/QPrinter>;
#include <QDir>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

////------
//    cout << QDir::currentPath().toStdString() << endl;
//    QString fileName(QDir::currentPath()+QString::fromStdString("/fuck.pdf"));
//    QTextDocument doc("hahaha");
//        QPrinter printer;
//        printer.setOutputFormat(QPrinter::PdfFormat);
//        printer.setOutputFileName(fileName);
//        doc.print(&printer); // doc is QTextDocument *

//    /*-----*/
//    cout << "printed to " << QDir::currentPath().toStdString() + "/fuck.pdf" << endl;
    return a.exec();
}
