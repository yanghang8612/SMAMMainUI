#include "smam_mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtCore>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QApplication a(argc, argv);

    QTranslator qtGloble;
    qtGloble.load("qt_zh-cn.qm");
    a.installTranslator(&qtGloble);

    QApplication::setStyle("Cleanlooks");

    QList<QString> list;

    list << "123";

    QList<QString>& otherList = list;

    list << "321";

    qDebug() << otherList.size();

    qDebug() << QSqlDatabase::drivers();

    SMAMMainWindow w;
    w.show();

    return a.exec();
}
