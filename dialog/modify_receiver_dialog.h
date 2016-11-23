#ifndef MODIFY_RECEIVER_DIALOG_H
#define MODIFY_RECEIVER_DIALOG_H

#include <QDialog>

namespace Ui {
	class ModifyReceiverDialog;
}

class ModifyReceiverDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ModifyReceiverDialog(QWidget *parent = 0);
	~ModifyReceiverDialog();

private:
	Ui::ModifyReceiverDialog *ui;
};

#endif // MODIFY_RECEIVER_DIALOG_H
