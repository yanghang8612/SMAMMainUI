#ifndef RECEIVER_EDIT_DIALOG_H
#define RECEIVER_EDIT_DIALOG_H

#include <QDialog>

#include "bean/receiver.h"

namespace Ui {
class ReceiverEditDialog;
}

class ReceiverEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiverEditDialog(QWidget *parent = 0);
    explicit ReceiverEditDialog(Receiver* receiver, QWidget *parent = 0);
    ~ReceiverEditDialog();

signals:
    void confirmButtonClicked(Receiver* receiver);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ReceiverEditDialog *ui;
    Receiver* receiver;
};

#endif // RECEIVER_EDIT_DIALOG_H
