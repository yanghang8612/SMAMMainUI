#ifndef ADD_STANDARDSTATION_DIALOG_H
#define ADD_STANDARDSTATION_DIALOG_H

#include <QDialog>

#include "station/standard_station.h"

namespace Ui {
	class AddStandardStationDialog;
}

class AddStandardStationDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddStandardStationDialog(QWidget *parent = 0);
	~AddStandardStationDialog();

signals:
	void confirmButtonClicked(StandardStation* station);

private slots:
	void on_confirmButton_clicked();
	void on_cancelButton_clicked();

private:
	Ui::AddStandardStationDialog *ui;
};

#endif // ADD_STANDARDSTATION_DIALOG_H
