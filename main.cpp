#include <QApplication>
#include <QDebug>
#include <QtCore>
#include <QTableWidgetItem>

#include <time.h>

#include "smam_mainwindow.h"
#include "main_component_header.h"
#include "smam_component_header.h"

extern "C" bool DllMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
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
                     QDialog {background: rgb(240,240,240);}\
                     QWidget {font-size: 13px}");
    w.show();

    //DllMain(0, 0);

    return a.exec();
}
