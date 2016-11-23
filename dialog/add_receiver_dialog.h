#ifndef ADD_RECEIVER_DIALOG_H
#define ADD_RECEIVER_DIALOG_H

#include <QDialog>

namespace Ui {
	class AddReceiverDialog;
}

class AddReceiverDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddReceiverDialog(QWidget *parent = 0);
	~AddReceiverDialog();

private:
	Ui::AddReceiverDialog *ui;
};

#endif // ADD_RECEIVER_DIALOG_H
