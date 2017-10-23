#include <QApplication>
#include <QDebug>
#include <QtCore>
#include <QTableWidgetItem>

#include <time.h>

#include "smam_mainwindow.h"
#include "main_component_header.h"
#include "smam_component_header.h"

extern "C" bool DllMain(int argc, char* argv[]);

FINDMEMORYINFOFUNC FindMemoryInfoFunc;
DLLSTATUSREADFUNC  DllStatusReadFunc;
DLLSTATUSWRITEFUNC DllStatusWriteFunc;
SOFTWORKSTATUSWRITEFUNC SoftWorkStatusWriteFunc;
REGISTERSIGNALLISTENER registerSignalListener;
REGISTERSIGNALSENDER registerSignalSender;

void* find(int memID, uint memLength)
{
    static QMap<int, void*> map;
    if (!map.contains(memID)) {
        void* pointer = malloc(memLength);
        qMemSet(pointer, 0, memLength);
        map.insert(memID, pointer);
    }
    return map[memID];
}

void method1(int*, int)
{}

bool method2(int)
{return true;}

bool method3(int,SoftWorkStatus)
{return true;}

bool method4(QObject*, const char*, const char*)
{return true;}

bool method5(QObject*)
{return true;}

int main(int argc, char* argv[])
{
    FindMemoryInfoFunc = find;
    DllStatusReadFunc = method1;
    DllStatusWriteFunc = method2;
    SoftWorkStatusWriteFunc = method3;
    registerSignalListener = method4;
    registerSignalSender = method5;
    char* arg[1];
    arg[0] = "BJ";
    DllMain(1, arg);

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QApplication a(argc, argv);

    QApplication::setStyle("Cleanlooks");
    QPalette standardPalette = QApplication::style()->standardPalette();
    standardPalette.setColor(QPalette::Background, QColor("#D4D0C8"));
    QApplication::setPalette(standardPalette);

    SMAMMainWindow w;
    w.setStyleSheet("QLineEdit {border: 1px solid white;border-radius: 3px;}\
                     QTabWidget::pane {background: rgb(212,208,200);}\
                     QTabWidget QGroupBox {border: 1px solid gray;margin-top: 10px;padding-top: 3px;}\
                     QTabWidget QGroupBox::title {top: -7px;left: 10px;}\
                     QDialog QGroupBox {border: 1px solid gray;margin-top: 10px;}\
                     QDialog QGroupBox::title {top: -7px;left: 10px;}\
                     QDialog {background: rgb(240,240,240);}");
    w.show();
    return a.exec();
}
