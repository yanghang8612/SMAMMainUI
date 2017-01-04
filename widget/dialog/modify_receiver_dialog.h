#ifndef MODIFY_RECEIVER_DIALOG_H
#define MODIFY_RECEIVER_DIALOG_H

#include <QDialog>

#include "bean/station/receiver.h"

namespace Ui {
	class ModifyReceiverDialog;
}

class ModifyReceiverDialog : public QDialog
{
	Q_OBJECT

public:
    explicit ModifyReceiverDialog(Receiver* receiver, QWidget *parent = 0);
	~ModifyReceiverDialog();

signals:
	void confirmButtonClicked(Receiver* receiver);

private slots:
	void on_confirmButton_clicked();
	void on_cancelButton_clicked();

private:
	Ui::ModifyReceiverDialog *ui;
	Receiver* receiver;
};

#endif // MODIFY_RECEIVER_DIALOG_H