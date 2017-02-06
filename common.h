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

const QString STANDARD_CONFIGFILE_PATH = "caster-config.xml";
const QString IGMAS_CONFIGFILE_PATH = "iGMAS-collector-cfg.xml";
const QString DATE_FORMAT_STRING = "yyyy-MM-dd";
const QString TIME_FORMAT_STRING = "hh:mm:ss";
const QString DATETIME_FORMAT_STRING = "yyyy-MM-dd hh:mm:ss";

const quint32 MAX_RECEIVER_COUNT_PERSTATION = 5;

const quint32 TABLEWIDGET_HORIZONHEADER_HEIGHT = 25;

const quint32 STANDARD_SHAREDBUFFER_ID = (quint8) 1601;
const quint32 STANDARD_SHAREDBUFFER_MAXITEMCOUNT = 200;
const quint32 OTHERCENTER_SHAREDBUFFER_ID = 1602;
const quint32 OTHERCENTER_SHAREDBUFFER_MAXITEMCOUNT = 200;

const quint32 DLLSTATUS_CHECK_TIMEINTERVAL = 3000;
const quint32 MESSAGE_CHECK_TIMEINTERVAL = 100;
const quint32 DLL_COUNT = 24;
const quint32 COMPONENT_DLL_COUNT[6] = {3, 2, 6, 4, 5, 4};
const quint32 COMPONENT_STATUSARRAY_INDEX[6] = {0, 3, 5, 11, 15, 20};

#endif // COMMON_H

