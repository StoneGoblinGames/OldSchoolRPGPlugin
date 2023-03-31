#pragma once

#include "CoreMinimal.h"
#include "Enum/ECharacterStates.h"
#include "FCharacterState.generated.h"

USTRUCT(BlueprintType)
struct FCharacterState
{
	GENERATED_BODY();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<ECharacterStates::State> State;

	bool operator==(const FCharacterState& Other) const
	{
		// Compare the relevant fields of the FCharacterState objects
		return (State == Other.State);
	}	
};
