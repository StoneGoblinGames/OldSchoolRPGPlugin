#pragma once

#include "CoreMinimal.h"
#include "Enum/EClasses.h"
#include "Enum/Spells/ESpellComponents.h"
#include "FSpell.generated.h"

USTRUCT(BlueprintType)
struct FSpell
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AffectedAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RequiresConcentration = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReversed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EClasses::Class>> Classes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Level;
	
};
