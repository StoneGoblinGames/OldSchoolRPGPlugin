#pragma once

#include "CoreMinimal.h"
#include "Enum/EClasses.h"
#include "FSpell.generated.h"

USTRUCT(BlueprintType)
struct FSpell : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReversed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EClasses::Class>> Classes;	
};
