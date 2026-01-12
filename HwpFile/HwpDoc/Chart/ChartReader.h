#ifndef CHARTREADER_H
#define CHARTREADER_H

#include "../HWPStream.h"

namespace HWP { namespace CHART
{
class CChartReader
{
public:
	CChartReader();

	bool ReadFromOle(CHWPStream& oOleData);
};
}}

#endif // CHARTREADER_H
