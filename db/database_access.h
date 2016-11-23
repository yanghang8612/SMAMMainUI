#ifndef DATABASEACCESS_H
#define DATABASEACCESS_H

#include <QtSql>

class DatabaseAccess
{
public:
	static bool connect(const QString& dbName);

private:
	DatabaseAccess();
};

#endif // DATABASEACCESS_H
