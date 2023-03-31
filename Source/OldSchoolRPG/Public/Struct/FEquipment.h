#pragma once

#include "CoreMinimal.h"
#include "Enum/ECharacterStates.h"
#include "Enum/EEquipmentType.h"
#include "FEquipment.generated.h"

USTRUCT(BlueprintType)
struct FEquipment : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FString InternalName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FullName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EEquipmentType::Type> Type = EEquipmentType::AdventuringGear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Weight = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<ECharacterStates::State>> GrantStatesWhenEquipped;
};
