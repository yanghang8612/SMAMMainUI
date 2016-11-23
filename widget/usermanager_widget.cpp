#include <QChar>
#include <QMenu>
#include <QMessageBox>

#include "usermanager_widget.h"
#include "ui_usermanager_widget.h"
#include "common.h"
#include "dialog/add_user_dialog.h"
#include "dialog/modify_user_dialog.h"
#include "dialog/view_user_dialog.h"

UserManagerWidget::UserManagerWidget(QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::UserManagerWidget)
{
	ui->setupUi(this);
	ui->userTable->horizontalHeader()->resizeSection(0, 150);
	ui->userTable->horizontalHeader()->resizeSection(3, 150);
	ui->userTable->horizontalHeader()->setFixedHeight(TABLEWIDGET_HORIZONHEADER_HEIGHT);
	ui->userTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->userTable->verticalHeader()->setVisible(false);
	ui->userTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->userTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showRightMenu(QPoint)));

	colunmName << "User_Name" << "User_Level" << "Terminal_Type" << "Terminal_ID" << "Service_Deadline";

	updateTable();
}

UserManagerWidget::~UserManagerWidget()
{
	delete ui;
}

void UserManagerWidget::showRightMenu(QPoint pos)
{
	QMenu* popMenu =new QMenu();
	QAction* addNewUser = new QAction(QIcon(":/user_add"), tr(" 添加用户"), this);
	addNewUser->setIconVisibleInMenu(true);
	connect(addNewUser, SIGNAL(triggered(bool)), this, SLOT(showAddNewUserDialog()));
	popMenu->addAction(addNewUser);

	if (ui->userTable->itemAt(pos) != NULL) {
	   QAction* deleteUser = new QAction(QIcon(":/user_delete"), tr(" 删除用户"), this);
	   deleteUser->setIconVisibleInMenu(true);
	   connect(deleteUser, SIGNAL(triggered(bool)), this, SLOT(deleteUser()));
	   popMenu->addAction(deleteUser);
	   QAction* modifyUser = new QAction(QIcon(":/user_modify"), tr(" 编辑用户信息"), this);
	   modifyUser->setIconVisibleInMenu(true);
	   connect(modifyUser, SIGNAL(triggered(bool)), this, SLOT(showModifyUserDialog()));
	   popMenu->addAction(modifyUser);
	   popMenu->addSeparator();
	   QAction* viewUser = new QAction(QIcon(":/user_view"), tr(" 查看用户信息"), this);
	   viewUser->setIconVisibleInMenu(true);
	   connect(viewUser, SIGNAL(triggered(bool)), this, SLOT(showViewUserDialog()));
	   popMenu->addAction(viewUser);
	}

	popMenu->exec(QCursor::pos());
}

void UserManagerWidget::showAddNewUserDialog()
{
	AddUserDialog* dialog = new AddUserDialog(this);
	connect(dialog, SIGNAL(confirmButtonClicked(BaseUser*)), this, SLOT(addNewUser(BaseUser*)));
	dialog->show();
}

void UserManagerWidget::addNewUser(BaseUser* user)
{
	int rowNum = data->rowCount();
	data->insertRow(rowNum);
	data->setData(data->index(rowNum, 1), user->getUserName());
	data->setData(data->index(rowNum, 2), user->getUserPassword());
	data->setData(data->index(rowNum, 3), QChar(user->getUserLevel()));
	data->setData(data->index(rowNum, 4), user->getServiceDeadline());
	data->setData(data->index(rowNum, 5), user->getTerminalType());
	data->setData(data->index(rowNum, 6), user->getTerminalID());
	data->submitAll();
	updateTable();
}

void UserManagerWidget::showModifyUserDialog()
{
	ModifyUserDialog* dialog = new ModifyUserDialog(this, new BaseUser(data->record(ui->userTable->currentRow())));
	connect(dialog, SIGNAL(confirmButtonClicked(BaseUser*)), this, SLOT(modifyUser(BaseUser*)));
	dialog->show();
}

void UserManagerWidget::modifyUser(BaseUser* user)
{
	int selectedRowIndex = ui->userTable->currentRow();
	data->setData(data->index(selectedRowIndex, 1), user->getUserName());
	data->setData(data->index(selectedRowIndex, 2), user->getUserPassword());
	data->setData(data->index(selectedRowIndex, 3), QChar(user->getUserLevel()));
	data->setData(data->index(selectedRowIndex, 4), user->getServiceDeadline());
	data->setData(data->index(selectedRowIndex, 5), user->getTerminalType());
	data->setData(data->index(selectedRowIndex, 6), user->getTerminalID());
	data->submitAll();
	updateTable();
}

void UserManagerWidget::deleteUser()
{
	QString content = "确认删除用户 " + ui->userTable->item(ui->userTable->currentRow(), 0)->text() + " 吗？";
	int ret = QMessageBox::warning(this,
								   tr("提示"),
								   content,
								   QMessageBox::Cancel | QMessageBox::Ok);
	if (ret == QMessageBox::Ok) {
		data->removeRow(ui->userTable->currentRow());
		data->submitAll();
		updateTable();
	}
}

void UserManagerWidget::showViewUserDialog()
{

}

void UserManagerWidget::updateTable()
{
	if (DatabaseAccess::connect(dbName)) {
		if (data != 0) {
			delete data;
		}
		data = new QSqlTableModel(this, QSqlDatabase::database(dbName));
		data->setTable("user_info");

		if (data->select()) {
			ui->userTable->clearContents();
			ui->userTable->setRowCount(data->rowCount());
			for (int i = 0; i < data->rowCount(); i++) {
				QSqlRecord record = data->record(i);
				for (int j = 0; j < colunmName.size(); j++) {
					ui->userTable->setItem(i, j, new QTableWidgetItem(record.value(colunmName[j]).toString()));
				}
			}
		}
	}
}
