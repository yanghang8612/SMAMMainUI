#ifndef MODIFY_COMPONENT_STATE_CHECK_INTERVALS_DIALOG_H
#define MODIFY_COMPONENT_STATE_CHECK_INTERVALS_DIALOG_H

#include <QDialog>

namespace Ui {
class ModifyComponentStateCheckIntervalsDialog;
}

class ModifyComponentStateCheckIntervalsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyComponentStateCheckIntervalsDialog(QList<int> componentStateCheckIntervals, QWidget *parent = 0);
    ~ModifyComponentStateCheckIntervalsDialog();

signals:
    void confirmButtonClicked(QList<int> componentStateCheckIntervals);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ModifyComponentStateCheckIntervalsDialog *ui;
    QList<int> componentStateCheckIntervals;
};

#endif // MODIFY_COMPONENT_STATE_CHECK_INTERVALS_DIALOG_H
