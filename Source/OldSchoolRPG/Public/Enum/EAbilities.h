#pragma once

UENUM(BlueprintType)
namespace EAbilities {
	enum Ability {
		STR UMETA(DisplayName="Strength"),
		DEX UMETA(DisplayName="Dexterity"),
		CON UMETA(DisplayName="Constitution"),
		INT UMETA(DisplayName="Intelligence"),
		WIS UMETA(DisplayName="Wisdom"),
		CHA UMETA(DisplayName="Charisma"),
	};
}
