#include "sysinfo.h"

#include <QtGlobal>

#ifdef Q_OS_WIN
#  include "sysinfowindowsimpl.h"
#elif defined(Q_OS_LINUX)
#  include "sysinfolinuximpl.h"
#elif defined(Q_OS_MAC)
#  include "sysinfomacimpl.h"
#endif

SysInfo::SysInfo()
{

}

SysInfo::~SysInfo()
{

}

SysInfo & SysInfo::instance()
{
#ifdef Q_OS_WIN
	static SysInfoWindowsImpl singleton;
#elif defined(Q_OS_LINUX)
	static SysInfoLinuxImpl singleton;
#elif defined(Q_OS_MAC)
	static SysInfoMacImpl singleton;
#endif

	return singleton;
}
