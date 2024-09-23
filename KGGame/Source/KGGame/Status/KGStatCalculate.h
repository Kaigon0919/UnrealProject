#pragma once

class KGStatCalculate
{
public:
	enum class CalculateType
	{
		Add = 0,
		Percent,
		Max
	};

private:
	float baseValue;
	float modifyValues[static_cast<int>(CalculateType::Max) + 1];
	float calculatedValue;
	bool isComplateCalculate;

public:
	KGStatCalculate();
public:
	float Get() 
	{ 
		if (false == isComplateCalculate)
		{
			Calc();
		}
		return calculatedValue; 
	};
	void SetBaseValue(const float value);
private:
	void Calc();
	void AddModifyValue(const CalculateType calcType, const float value);

};