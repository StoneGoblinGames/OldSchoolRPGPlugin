#pragma once

#include "CoreMinimal.h"
#include "FWeaponStats.generated.h"

USTRUCT(BlueprintType)
struct FWeaponStats : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Qualities;
};
