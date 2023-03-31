#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FClassProperties.generated.h"

USTRUCT(BlueprintType)
struct FClassProperties : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EClasses::Class> ClassName = EClasses::Fighter;

	UPROPERTY(BlueprintReadOnly)
	FString Requirements;

	UPROPERTY(BlueprintReadOnly)
	FString PrimeRequisite;

	UPROPERTY(BlueprintReadOnly)
	FString HitDice = "1d4";

	UPROPERTY(BlueprintReadOnly)
	int32 MaxLevel = 14;

	UPROPERTY(BlueprintReadOnly)
	FString Armour;

	UPROPERTY(BlueprintReadOnly)
	FString Weapons;

	UPROPERTY(BlueprintReadOnly)
	FString Languages;

	UPROPERTY(BlueprintReadOnly)
	FString Description;

	UPROPERTY(BlueprintReadOnly)
	int32 SaveD = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 SaveW = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 SaveP = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 SaveB = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 SaveS = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 THAC0 = 19;	

	UPROPERTY(BlueprintReadOnly)
	FString ClassSkills;

	UPROPERTY(BlueprintReadOnly)
	FString ClassFeatures;		
};
