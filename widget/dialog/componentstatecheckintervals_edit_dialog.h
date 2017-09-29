#ifndef COMPONENTSTATECHECKINTERVALS_EDIT_DIALOG_H
#define COMPONENTSTATECHECKINTERVALS_EDIT_DIALOG_H

#include <QDialog>

namespace Ui {
class ComponentStateCheckIntervalsEditDialog;
}

class ComponentStateCheckIntervalsEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComponentStateCheckIntervalsEditDialog(QWidget *parent = 0);
    ~ComponentStateCheckIntervalsEditDialog();

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ComponentStateCheckIntervalsEditDialog *ui;
};

#endif // COMPONENTSTATECHECKINTERVALS_EDIT_DIALOG_H
