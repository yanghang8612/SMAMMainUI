#include <QMessageBox>

#include "database_access.h"

bool DatabaseAccess::connect(const QString& dbName)
{
	if (QSqlDatabase::contains(dbName)) {
		return true;
	}

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", dbName);
	db.setHostName("127.0.0.1");
	db.setUserName("root");
	db.setPassword("8612");
	db.setDatabaseName("BDLSS");

	if (!db.open()) {
		QMessageBox::critical(0, QObject::tr("Database Error"),
							  db.lastError().text());
		return false;
	}
	return true;
}

DatabaseAccess::DatabaseAccess()
{

}

