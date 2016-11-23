#ifndef ADD_STANDARDSTATION_DIALOG_H
#define ADD_STANDARDSTATION_DIALOG_H

#include <QDialog>

namespace Ui {
	class AddStandardStationDialog;
}

class AddStandardStationDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddStandardStationDialog(QWidget *parent = 0);
	~AddStandardStationDialog();

private:
	Ui::AddStandardStationDialog *ui;
};

#endif // ADD_STANDARDSTATION_DIALOG_H
