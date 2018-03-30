#include "datacenter_select_dialog.h"
#include "ui_datacenter_select_dialog.h"

#include "utilities/config_helper.h"

DataCenterSelectDialog::DataCenterSelectDialog(const QString& dataCenters, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataCenterSelectDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("添加数据源"));
    QStringList dataCenterList = dataCenters.split(",", QString::SkipEmptyParts);
    for (int i = 0; i < ConfigHelper::dataCenters.size(); i++) {
        QString centerID = QString::number(ConfigHelper::dataCenters[i]->getCenterID());
        if (!dataCenterList.contains(centerID)) {
            QListWidgetItem* listItem = new QListWidgetItem(
                                            QIcon(":/datacenter"),
                                            ConfigHelper::dataCenters[i]->getCenterName());
            listItem->setData(Qt::UserRole, QVariant(centerID));
            listItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            listItem->setCheckState(Qt::Unchecked);
            ui->dataCenterList->addItem(listItem);
        }
    }
}

DataCenterSelectDialog::~DataCenterSelectDialog()
{
    delete ui;
}

void DataCenterSelectDialog::on_confirmButton_clicked()
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

void DataCenterSelectDialog::on_cancelButton_clicked()
{
    QDialog::reject();
}
