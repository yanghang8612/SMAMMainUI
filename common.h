#ifndef COMMON_H
#define COMMON_H

#include <QtCore>
#include <QtGui>

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

const int TABLEWIDGET_HORIZONHEADER_HEIGHT = 25;

#endif // COMMON_H

