#pragma once

#include "CoreMinimal.h"
#include "Enum/ECoins.h"
#include "FCoinTreasure.generated.h"

USTRUCT(BlueprintType)
struct FCoinTreasure
{
	GENERATED_BODY();
	FCoinTreasure()
	{
		Coin = ECoins::Copper;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECoins::Coin> Coin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 0;
};
