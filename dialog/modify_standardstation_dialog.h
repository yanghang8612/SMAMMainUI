#ifndef MODIFY_STANDARDSTATION_DIALOG_H
#define MODIFY_STANDARDSTATION_DIALOG_H

#include <QDialog>

#include "station/standard_station.h"

namespace Ui {
	class ModifyStandardStationDialog;
}

class ModifyStandardStationDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ModifyStandardStationDialog(QWidget *parent = 0, StandardStation* station = 0);
	~ModifyStandardStationDialog();

signals:
	void confirmButtonClicked(StandardStation* station);

private slots:
	void on_confirmButton_clicked();
	void on_cancelButton_clicked();

private:
	Ui::ModifyStandardStationDialog *ui;
	StandardStation* station;
};

#endif // MODIFY_STANDARDSTATION_DIALOG_H
