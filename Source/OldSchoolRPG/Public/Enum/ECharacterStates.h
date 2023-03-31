#pragma once

UENUM(BlueprintType)
namespace ECharacterStates {
	enum State {
		HasWeaponEquipped UMETA(DisplayName="Has weapon equipped"),
		HasArmourEquipped UMETA(DisplayName="Has armour equipped"),
		HasShieldEquipped UMETA(DisplayName="Has shield equipped"),
		HasRangedWeaponEquipped UMETA(DisplayName="Has ranged weapon equipped"),
		HasTwoHandedWeaponEquipped UMETA(DisplayName="Has two-handed weapon equipped"),
		HasSlowWeaponEquipped UMETA(DisplayName="Has slow weapon equipped"),
		HasBluntWeaponEquipped UMETA(DisplayName="Has blunt weapon equipped"),
		HasReloadWeaponEquipped UMETA(DisplayName="Has reload weapon equipped"),
		HasSplashWeaponEquipped UMETA(DisplayName="Has splash weapon equipped"),
		HasChargeWeaponEquipped UMETA(DisplayName="Has charge weapon equipped"),
		HasBraceWeaponEquipped UMETA(DisplayName="Has brace weapon equipped"),
		IsOnFire UMETA(DisplayName="Is on fire"),
		IsFrozen UMETA(DisplayName="Is frozen"),
		IsElectrocuted UMETA(DisplayName="Is electrocuted"),
		IsStunned UMETA(DisplayName="Is stunned"),
		IsCharmed UMETA(DisplayName="Is charmed"),
	};	
}
