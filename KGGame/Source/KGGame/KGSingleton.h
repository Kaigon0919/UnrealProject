// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KGSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogKGSingleton, Error, All);

/**
 * 
 */

/// <summary>
/// 필요한 Singleton을 UKGSingleton에서 맴버변수로 만들어 사용하도록 합니다.
/// </summary>
UCLASS()
class KGGAME_API UKGSingleton : public UObject
{
	GENERATED_BODY()
public:
	UKGSingleton();

public:
	static UKGSingleton* Get();

public:
	void initialize();
	
private:
	// TODO. 데이터 로드 관련된 class 추가(StaticInfo)
	
};
