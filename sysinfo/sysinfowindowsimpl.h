#ifndef SYSINFOWINDOWSIMPL_H
#define SYSINFOWINDOWSIMPL_H

#include <QtGlobal>
#include <qvector.h>

#include "sysinfo.h"

typedef struct _FILETIME FILETIME;

class SysInfoWindowsImpl : public SysInfo
{
public:
	SysInfoWindowsImpl();

	// SysInfo interface
public:
	void init() override;
	double cpuLoadAverage() override;
	double memoryUsed() override;

private:
	QVector<qulonglong> cpuRawData();
	qulonglong convertFileTime(const FILETIME & filetime) const;
	QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOWINDOWSIMPL_H
