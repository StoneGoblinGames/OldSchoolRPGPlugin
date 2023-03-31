#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FRaceProperties.generated.h"

USTRUCT(BlueprintType)
struct FRaceProperties : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ERaces::Race> Name = ERaces::Human;

	UPROPERTY(BlueprintReadOnly)
	FString Description;

	UPROPERTY(BlueprintReadOnly)
	FString Requirements;

	UPROPERTY(BlueprintReadOnly)
	FString AbilityModifiers;

	UPROPERTY(BlueprintReadOnly)
	FString Languages;

	UPROPERTY(BlueprintReadOnly)
	FString ClassRestrictions;

	UPROPERTY(BlueprintReadOnly)
	FString Features;
};
