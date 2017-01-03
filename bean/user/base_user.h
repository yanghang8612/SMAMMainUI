#ifndef BASEUSER_H
#define BASEUSER_H

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QSqlRecord>

class BaseUser
{
public:
	BaseUser();
	BaseUser(const QSqlRecord& record);

	QString getUserName() const;
	void setUserName(const QString& value);

	QString getUserPassword() const;
	void setUserPassword(const QString& value);

	char getUserLevel() const;
	void setUserLevel(char value);
	void setUserLevel(QString value);

	QDateTime getServiceDeadline() const;
	void setServiceDeadline(const QDateTime& value);

	quint8 getTerminalType() const;
	void setTerminalType(const quint8& value);

	QString getTerminalID() const;
	void setTerminalID(const QString& value);

	QSqlRecord* toSQLRecord();

private:
	QString userName;
	QString userPassword;
	char userLevel;
	QDateTime serviceDeadline;
	quint8 terminalType;
	QString terminalID;
};

#endif // BASEUSER_H
