#include "ChartReader.h"

#include "VtChart.h"

namespace HWP { namespace CHART
{
CChartReader::CChartReader()
{

}

bool CChartReader::ReadFromOle(CHWPStream& oOleData)
{
	oOleData.Skip(44); //Unknown data

	short shStoredNameLength;
	oOleData.ReadShort(shStoredNameLength);

	HWP_STRING sStoredName;
	oOleData.ReadString(sStoredName, shStoredNameLength, EStringCharacter::ASCII);

	// if ("VtChart" == sStoredName)


	CVtChart oVtChart;

	if (!oVtChart.Read(oOleData))
		return false;

	return false;
}
}}
