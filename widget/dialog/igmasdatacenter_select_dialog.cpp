#include "igmasdatacenter_select_dialog.h"
#include "ui_igmasdatacenter_select_dialog.h"

#include "utilities/config_helper.h"

iGMASDataCenterSelectDialog::iGMASDataCenterSelectDialog(const QString& dataCenters, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::iGMASDataCenterSelectDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("添加数据源"));
    QStringList dataCenterList = dataCenters.split(",", QString::SkipEmptyParts);
    for (int i = 0; i < ConfigHelper::iGMASDataCenters.size(); i++) {
        QString centerID = QString::number(ConfigHelper::iGMASDataCenters[i]->getCenterID());
        if (!dataCenterList.contains(centerID)) {
            QListWidgetItem* listItem = new QListWidgetItem(
                                            QIcon(":/datacenter"),
                                            ConfigHelper::iGMASDataCenters[i]->getCenterName());
            listItem->setData(Qt::UserRole, QVariant(centerID));
            listItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            listItem->setCheckState(Qt::Unchecked);
            ui->dataCenterList->addItem(listItem);
        }
    }
}

iGMASDataCenterSelectDialog::~iGMASDataCenterSelectDialog()
{
    delete ui;
}

void iGMASDataCenterSelectDialog::on_confirmButton_clicked()
{
    QString newDataCenters = "";
    for (int i = 0; i < ui->dataCenterList->count(); i++) {
        if (ui->dataCenterList->item(i)->checkState() == Qt::Checked) {
            newDataCenters += (ui->dataCenterList->item(i)->data(Qt::UserRole).toString() + ",");
        }
    }

    emit confirmButtonClicked(newDataCenters);
    QDialog::accept();
}

void iGMASDataCenterSelectDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
