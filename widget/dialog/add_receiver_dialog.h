#ifndef ADD_RECEIVER_DIALOG_H
#define ADD_RECEIVER_DIALOG_H

#include <QDialog>

#include "bean/station/receiver.h"

namespace Ui {
	class AddReceiverDialog;
}

class AddReceiverDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddReceiverDialog(QWidget *parent = 0);
	~AddReceiverDialog();

signals:
	void confirmButtonClicked(Receiver* receiver);

private slots:
	void on_confirmButton_clicked();
	void on_cancelButton_clicked();

private:
	Ui::AddReceiverDialog *ui;
};

#endif // ADD_RECEIVER_DIALOG_H
