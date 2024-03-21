#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EAlliance : uint8
{
	None,
	Player,
	Enemy
};

bool IsEnemy(const EAlliance des, const EAlliance src);