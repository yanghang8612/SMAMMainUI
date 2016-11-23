#include "useronline_widget.h"
#include "ui_useronline_widget.h"
#include "common.h"

UserOnlineWidget::UserOnlineWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::UserOnlineWidget)
{
	ui->setupUi(this);
	ui->onlineUserTable->horizontalHeader()->resizeSection(2, 200);
	ui->onlineUserTable->horizontalHeader()->setFixedHeight(TABLEWIDGET_HORIZONHEADER_HEIGHT);
	ui->onlineUserTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->onlineUserTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->onlineUserTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->onlineUserTable->verticalHeader()->setVisible(false);

	startTimer(1000);
	updateTable();
}

UserOnlineWidget::~UserOnlineWidget()
{
	delete ui;
}

void UserOnlineWidget::updateTable()
{
	if (DatabaseAccess::connect(dbName)) {
		if (data != 0) {
			delete data;
		}
		data = new QSqlRelationalTableModel(this, QSqlDatabase::database(dbName));
		data->setTable("login_info");
		data->setRelation(1, QSqlRelation("user_info", "ID", "User_Name"));

		if (data->select()) {
			ui->onlineUserTable->clearContents();
			ui->onlineUserTable->setRowCount(data->rowCount());
			for (int i = 0; i < data->rowCount(); i++) {
				QSqlRecord record = data->record(i);
				ui->onlineUserTable->setItem(i, 0, new QTableWidgetItem(record.value("User_Name").toString()));
				ui->onlineUserTable->setItem(i, 1, new QTableWidgetItem(record.value("IP").toString() + ":" + record.value("Port").toString()));
				ui->onlineUserTable->setItem(i, 2, new QTableWidgetItem(tr("未知")));
				QDateTime loginTime = record.value("Login_Time").toDateTime();
				ui->onlineUserTable->setItem(i, 3, new QTableWidgetItem(loginTime.toString("yyyy年MM月dd日HH:mm:ss")));
				ui->onlineUserTable->setItem(i, 4, new QTableWidgetItem(QString::number(loginTime.secsTo(QDateTime::currentDateTime()))));
				ui->onlineUserTable->setItem(i, 5, new QTableWidgetItem(tr("付费用户")));
			}
		}
	}
}

void UserOnlineWidget::timerEvent(QTimerEvent* event)
{
	for (int i = 0; i < ui->onlineUserTable->rowCount(); i++) {
		int currentValue = ui->onlineUserTable->item(i, 4)->text().toInt();
		ui->onlineUserTable->setItem(i, 4, new QTableWidgetItem(QString::number(currentValue + 1)));
	}
}
