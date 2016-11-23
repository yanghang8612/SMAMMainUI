#ifndef BASEUSER_H
#define BASEUSER_H

#include <QObject>

class BaseUser : public QObject
{
	Q_OBJECT
public:
	explicit BaseUser(QObject *parent = 0);

signals:

public slots:
};

#endif // BASEUSER_H
