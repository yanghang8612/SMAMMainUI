#include <QWidget>
#include <QDebug>

#include "widget/mid/systemmanager_widget.h"

extern "C" bool DllMain(int argc, char* argv[])
{
    qDebug() << "SMAM DllMain function called.";
    return true;
}

extern "C" bool DllInit(int argc, char* argv[])
{
    qDebug() << "SMAM DllInit function called.";
    return true;
}

extern "C" bool DllStart()
{
    qDebug() << "SMAM DllStart function called.";
    return true;
}

extern "C" bool DllStop()
{
    qDebug() << "SMAM DllStop function called.";
    return true;
}

extern "C" bool DllContraryInit()
{
    qDebug() << "SMAM DllContraryInit function called.";
    return true;
}

extern "C" QWidget* getUIWidget(QWidget* parent = 0)
{
    return new SystemManagerWidget((DeploymentType::Value) 0, parent);
}
