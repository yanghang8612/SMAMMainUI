#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDateTime>

namespace DeploymentType {
	enum Value {
		XJ_CENTER,
		BJ_CENTER
	};
}

namespace CasterMode {
	enum Value {
		IMMEDIATE_CASTER,
		PROCESS_CASTER
	};
}

const QString XJ_CONFIGFILE_PATH = "xj-config.xml";
const QString BJ_CONFIGFILE_PATH = "bj-config.xml";
const QString DATE_FORMAT_STRING = "yyyy-MM-dd";
const QString TIME_FORMAT_STRING = "hh:mm:ss";
const QString DATETIME_FORMAT_STRING = "yyyy-MM-dd hh:mm:ss";

const quint32 MAX_RECEIVER_COUNT_PERSTATION = 5;

const quint32 TABLEWIDGET_HORIZONHEADER_HEIGHT = 25;

const quint32 RECEIVER_SHAREDBUFFER_ID = 1601;
const quint32 RECEIVER_SHAREDBUFFER_MAXITEMCOUNT = 200;
const quint32 OTHERCENTER_SHAREDBUFFER_ID = 1602;
const quint32 OTHERCENTER_SHAREDBUFFER_MAXITEMCOUNT = 200;
const quint32 IGMAS_SHAREDBUFFER_ID = 1603;
const quint32 IGMAS_SHAREDBUFFER_MAXITEMCOUNT = 20;

const quint32 DLLSTATUS_CHECK_TIMEINTERVAL = 3000;
const quint32 MESSAGE_CHECK_TIMEINTERVAL = 100;
const quint32 COMPONENT_COUNT = 6;
const quint32 DLL_COUNT = 24;
const quint32 COMPONENT_DLL_COUNT[COMPONENT_COUNT] = {3, 2, 6, 4, 5, 4};
const quint32 COMPONENT_STATUSARRAY_INDEX[COMPONENT_COUNT] = {0, 3, 5, 11, 15, 20};

#endif // COMMON_H

