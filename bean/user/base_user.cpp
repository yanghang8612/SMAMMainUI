#include <QChar>

#include "base_user.h"

BaseUser::BaseUser()
{

}

BaseUser::BaseUser(const QSqlRecord& record)
{
	userName = record.value(1).toString();
	userPassword = record.value(2).toString();
	userLevel = record.value(3).toString().at(0).toAscii();
	serviceDeadline = record.value(4).toDateTime();
	terminalType = record.value(5).toChar().unicode();
	terminalID = record.value(6).toString();
}

QString BaseUser::getUserName() const
{
    return userName;
}

void BaseUser::setUserName(const QString& value)
{
    userName = value;
}

QString BaseUser::getUserPassword() const
{
    return userPassword;
}

void BaseUser::setUserPassword(const QString& value)
{
    userPassword = value;
}

char BaseUser::getUserLevel() const
{
    return userLevel;
}

void BaseUser::setUserLevel(char value)
{
	userLevel = value;
}

void BaseUser::setUserLevel(QString value)
{
	userLevel = value.at(0).toAscii();
}

QDateTime BaseUser::getServiceDeadline() const
{
    return serviceDeadline;
}

void BaseUser::setServiceDeadline(const QDateTime& value)
{
    serviceDeadline = value;
}

quint8 BaseUser::getTerminalType() const
{
    return terminalType;
}

void BaseUser::setTerminalType(const quint8& value)
{
    terminalType = value;
}

QString BaseUser::getTerminalID() const
{
    return terminalID;
}

void BaseUser::setTerminalID(const QString& value)
{
	terminalID = value;
}

QSqlRecord* BaseUser::toSQLRecord()
{
	QSqlRecord* record = new QSqlRecord();
	record->setValue("User_Name", userName);
	record->setValue("User_Password", userPassword);
	record->setValue("User_Level", QChar(userLevel));
	record->setValue("Service_Deadline", serviceDeadline);
	record->setValue("Terminal_Type", terminalType);
	record->setValue("Terminal_ID", terminalID);
	return record;
}







