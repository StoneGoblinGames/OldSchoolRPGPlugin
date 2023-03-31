#pragma once

#include "CoreMinimal.h"
#include "FEquipmentItem.h"
#include "Enum/ERaces.h"
#include "Enum/EClasses.h"
#include "Engine/DataTable.h"
#include "FCharacterValues.generated.h"

USTRUCT(BlueprintType)
struct FCharacterValues
{
	GENERATED_BODY();
	FCharacterValues()
	{
		Race = ERaces::Human;
		Class = EClasses::Fighter;
		InitialGold = 0;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ERaces::Race> Race;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EClasses::Class> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Background;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Alignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PrimeRequisite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackRoll = 19;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DeathSave = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WandSave = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ParalysisSave = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BreathSave = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpellSave = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Strength = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Dexterity = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Constitution = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Intelligence = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Wisdom = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Charisma = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ArmorClass = 9;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Initiative = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Speed = 120;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HitPoints = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HitDice = "1d4";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEquipmentItem> Equipment;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Features;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Spells;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InitialGold;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CharacterProgression = nullptr;
};
