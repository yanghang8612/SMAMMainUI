#ifndef SMAM_MAINWINDOW_H
#define SMAM_MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>

namespace Ui {
    class SMAMMainWindow;
}

class SMAMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMAMMainWindow(QWidget *parent = 0);
    ~SMAMMainWindow();

private slots:
    void handleManagerCloseMessage();
    void on_systemManagerAction_triggered(bool checked);

private:
    Ui::SMAMMainWindow *ui;

    QMdiSubWindow* systemManagerSub;
};

#endif // SMAM_MAINWINDOW_H
