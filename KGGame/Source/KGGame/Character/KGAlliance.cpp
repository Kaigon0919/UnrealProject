#include "KGAlliance.h"

namespace KG
{
	bool IsEnemy(const EAlliance des, const EAlliance src)
	{
		if (EAlliance::None == des || EAlliance::None == src)
		{
			return false;
		}

		if (des == src)
		{
			return false;
		}

		return true;
	}
}