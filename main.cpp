#include <QApplication>
#include <QDebug>
#include <QtCore>

#include "smam_mainwindow.h"
#include "mainframework_header.h"

int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QApplication a(argc, argv);

    QApplication::setStyle("Cleanlooks");

    SMAMMainWindow w;
    w.show();

    return a.exec();
}
