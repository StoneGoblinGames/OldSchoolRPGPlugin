#pragma once

UENUM(BlueprintType)
namespace EEquipmentType {
	enum Type {
		AdventuringGear UMETA(DisplayName="Adventuring gear"),
		Weapon UMETA(DisplayName="Weapon"),
		Armour UMETA(DisplayName="Armour"),
		Ammunition UMETA(DisplayName="Ammunition"),
		Misc UMETA(DisplayName="Misc."),
	};
}
