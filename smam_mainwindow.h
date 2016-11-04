#ifndef SMAMMAINWINDOW_H
#define SMAMMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SMAMMainWindow;
}

class SMAMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMAMMainWindow(QWidget *parent = 0);
    ~SMAMMainWindow();

private:
    Ui::SMAMMainWindow *ui;
};

#endif // SMAMMAINWINDOW_H
