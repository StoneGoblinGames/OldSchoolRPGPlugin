#pragma once

UENUM(BlueprintType)
namespace EEquipmentSlot {
	enum Slot {
		Head UMETA(DisplayName="Head"),
		Pendant UMETA(DisplayName="Pendant"),
		Gloves UMETA(DisplayName="Gloves"),
		RingLeft UMETA(DisplayName="Left ring"),
		RingRight UMETA(DisplayName="Right ring"),
		WeaponLeft UMETA(DisplayName="Left hand"),
		WeaponRight UMETA(DisplayName="Right hand"),
		Armour UMETA(DisplayName="Armour"),
		Feet UMETA(DisplayName="Feet"),
	};
}
