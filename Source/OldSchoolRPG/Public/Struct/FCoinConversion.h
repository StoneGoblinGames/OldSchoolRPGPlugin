#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/ECoins.h"
#include "FCoinConversion.generated.h"

USTRUCT(BlueprintType)
struct FCoinConversion : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ECoins::Coin> CoinName = ECoins::Platinum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double Platinum = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double Gold = 0.2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double Electrum = 0.1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double Silver = 0.02;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double Copper = 0.002;
};
