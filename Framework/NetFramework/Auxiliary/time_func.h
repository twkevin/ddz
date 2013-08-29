#ifndef __QX_TIME_H__
#define __QX_TIME_H__

#include "raw_type.h"
#include "common_macro_define.h"

NS_QX_BEGIN

struct qx_timeval
{
	qxInt32	tv_sec;		// seconds
	qxInt32	tv_usec;    // microSeconds
};

class QX_DLL CQXTime
{
public:
	CQXTime();
	~CQXTime();

	static qxInt32 getTimeOfDay(struct qx_timeval *tp, void *tzp);
	static qxInt32 getTime();
};

#define CURRENT_TIME CQXTime::getTime()
#define timeofday(tp, tzp) CQXTime::getTimeOfDay(tp, tzp)

NS_QX_END

#endif // __QX_TIME_H__