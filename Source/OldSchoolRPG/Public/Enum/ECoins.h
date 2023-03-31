#pragma once

UENUM(BlueprintType)
namespace ECoins {
	enum Coin {
		Copper UMETA(DisplayName="Copper"),
		Silver UMETA(DisplayName="Silver"),
		Electrum UMETA(DisplayName="Electrum"),
		Gold UMETA(DisplayName="Gold"),
		Platinum UMETA(DisplayName="Platinum"),
	};
}
