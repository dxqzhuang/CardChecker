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


    return a.exec();
}
