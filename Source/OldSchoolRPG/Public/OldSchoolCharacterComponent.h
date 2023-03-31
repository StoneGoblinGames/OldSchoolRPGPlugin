// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Struct/FCharacterValues.h"
#include "Components/ActorComponent.h"
#include "Enum/EClasses.h"
#include "Enum/EEquipmentSlot.h"
#include "Enum/ERaces.h"
#include "Libraries/OldSchoolRPGTables.h"
#include "Struct/FCharacterState.h"
#include "Struct/FCoinTreasure.h"
#include "OldSchoolCharacterComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogOldSchoolRPGCharacterComponent, Log, All);

UCLASS( Blueprintable )
class OLDSCHOOLRPG_API UOldSchoolCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOldSchoolCharacterComponent();

	UFUNCTION(BlueprintCallable, Category="Set up")
	void InitializeCharacter(FCharacterValues Values);
	UFUNCTION(BlueprintPure, Category="Game")
	int32 AddExperience(int32 BaseValue, bool PrimeRequisiteBonus = true);
	UFUNCTION(BlueprintPure, Category="Game")
	int32 GenerateBasicRoll(FString DiceRoll);
	UFUNCTION(BlueprintPure, Category="Game")
	bool AddCoins(FCoinTreasure CoinsToAdd);
	UFUNCTION(BlueprintPure, Category="Game")
	uint8 GetRetainerLimit() const;
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool HasItemEquipped(EEquipmentSlot::Slot Slot);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void EquipItem(EEquipmentSlot::Slot Slot, FEquipmentItem Item);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	FEquipmentItem UnEquipItem(EEquipmentSlot::Slot Slot);
	UPROPERTY(VisibleDefaultsOnly)
	UBlueprintFunctionLibrary* DiceRollerLibrary;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int32 GetPrimeRequisiteXPModifier();
	bool LevelUp();
	bool LevelUpAdvanced(FCharacterValues LevelUpValues);
	int32 GenerateRoll(FString DiceRoll);
	int32 RollHitPoints(FString HitPoints);
	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ERaces::Race> Race;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EClasses::Class> Class;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Background;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Alignment;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString PrimeRequisite;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AttackRoll;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DeathSave;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 WandSave;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ParalysisSave;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BreathSave;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SpellSave;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Level;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Strength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Dexterity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Constitution;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Intelligence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Wisdom;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Charisma;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ArmorClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Initiative;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 HitPoints;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString HitDice;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FEquipmentItem> Equipment;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> Features;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> Spells;
	UPROPERTY(BlueprintReadOnly)
	int32 Experience = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDataTable* CharacterProgression;		
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<TEnumAsByte<ECoins::Coin>, int32> Coins;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<TEnumAsByte<EEquipmentSlot::Slot>, FEquipmentItem> EquipmentMap;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FCharacterState> States;
};
