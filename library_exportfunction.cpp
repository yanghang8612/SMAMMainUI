#include <QWidget>

#include "widget/mid/systemmanager_widget.h"

extern "C" bool DllMain(int argc, char* argv[])
{
    return true;
}

extern "C" bool DllInit(int argc, char* argv[])
{
    return true;
}

extern "C" bool DllStart()
{
    return true;
}

extern "C" bool DllStop()
{
    return true;
}

extern "C" bool DllContraryInit()
{
    return true;
}

extern "C" QWidget* getUIWidget(QWidget* parent = 0)
{
    return 0;
}
