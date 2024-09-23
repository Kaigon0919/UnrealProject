#pragma once
#include "CoreMinimal.h"
#include "string"
#include "vector"

enum class KGSpecificStateType : int8
{
	None = -1,
	Invincibility = 0,
	Avoid = 1,
	Max
};

class KGSpecificState
{
public:
	KGSpecificState()
	{
		state = 0;
	}

	KGSpecificState(KGSpecificStateType type)
	{
		state = 1 << static_cast<int8>(type);
	}

private:
	int8 state;

public:
	void ToggleState(const KGSpecificStateType type);
	void OffState(const KGSpecificStateType type);
	void OnState(const KGSpecificStateType type);
	
	void GetSpecificStateDatas(_Out_ std::vector<KGSpecificStateType>& arrayStateTypes);
};

