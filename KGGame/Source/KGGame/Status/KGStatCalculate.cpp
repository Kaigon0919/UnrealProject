#include "KGStatCalculate.h"

KGStatCalculate::KGStatCalculate() : baseValue(0), calculatedValue(0), isComplateCalculate(false)
{
	const int max = modifyValues[static_cast<int>(CalculateType::Max)];
	for (int i = 0; i < max; ++i)
	{
		modifyValues[i] = 0;
	}
}

void KGStatCalculate::Calc()
{
	calculatedValue = baseValue;

	calculatedValue += modifyValues[static_cast<int>(CalculateType::Add)];
	calculatedValue += baseValue * modifyValues[static_cast<int>(CalculateType::Percent)];

	static_assert(static_cast<int>(CalculateType::Max) == 2);
	isComplateCalculate = true;
}

void KGStatCalculate::SetBaseValue(const float value)
{
	isComplateCalculate = false;
	baseValue = value;
}

void KGStatCalculate::AddModifyValue(const CalculateType calcType, const float value)
{
	isComplateCalculate = false;
	const __int32 arrayIndex = static_cast<__int32>(calcType);
	modifyValues[arrayIndex] += value;
}
