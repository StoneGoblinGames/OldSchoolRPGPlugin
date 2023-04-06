#pragma once

#include "CoreMinimal.h"
#include "FClassRequirement.generated.h"

USTRUCT(BlueprintType)
struct FClassRequirement
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Property;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Value {0};
};
