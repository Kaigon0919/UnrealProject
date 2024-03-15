#pragma once

#include "CoreMinimal.h"

namespace KG
{
	enum class EAlliance : uint8
	{
		None,
		Player,
		Enemy
	};

	bool IsEnemy(const EAlliance des, const EAlliance src);
};