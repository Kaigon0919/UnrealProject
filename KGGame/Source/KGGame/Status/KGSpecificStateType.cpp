#include "KGSpecificStateType.h"

void KGSpecificState::ToggleState(const KGSpecificStateType type)
{
	if (KGSpecificStateType::None == type)
	{
		return;
	}

	state ^= 1 << static_cast<int8>(type);
}

void KGSpecificState::OffState(const KGSpecificStateType type)
{
	if (KGSpecificStateType::None == type)
	{
		return;
	}

	state &= ~(1 << static_cast<int8>(type));
}

void KGSpecificState::OnState(const KGSpecificStateType type)
{
	if (KGSpecificStateType::None == type)
	{
		return;
	}

	state |= 1 << static_cast<int8>(type);
}

void KGSpecificState::GetSpecificStateDatas(std::vector<KGSpecificStateType>& arrayStateTypes)
{
	const int8 soruce = static_cast<int8>(this->state);
	const int8 max = static_cast<int8>(KGSpecificStateType::Max);
	std::vector<KGSpecificStateType> list(max);

	for (int8 i = 0; i < max; ++i)
	{
		if (0 < (soruce & (1 << i) ) )
		{
			list.push_back(static_cast<KGSpecificStateType>(i));
		}
	}
}
