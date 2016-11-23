#ifndef MODIFY_STANDARDSTATION_DIALOG_H
#define MODIFY_STANDARDSTATION_DIALOG_H

#include <QDialog>

namespace Ui {
	class ModifyStandardStationDialog;
}

class ModifyStandardStationDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ModifyStandardStationDialog(QWidget *parent = 0);
	~ModifyStandardStationDialog();

private:
	Ui::ModifyStandardStationDialog *ui;
};

#endif // MODIFY_STANDARDSTATION_DIALOG_H
