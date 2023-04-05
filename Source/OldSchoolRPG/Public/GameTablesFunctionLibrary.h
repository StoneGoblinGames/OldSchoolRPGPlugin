// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PluginDescriptor.h"
#include "Enum/EArmour.h"
#include "Enum/EClasses.h"
#include "Enum/ECoins.h"
#include "Enum/EEquipmentType.h"
#include "Enum/ERaces.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Struct/FCharacterState.h"
#include "Struct/FClassProperties.h"
#include "Struct/FEquipment.h"
#include "Struct/Spells/FSpell.h"
#include "Struct/FRaceProperties.h"
#include "Struct/FClassLevel.h"
#include "Struct/FWeaponStats.h"
#include "Struct/FCoinConversion.h"
#include "GameTablesFunctionLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogOldSchoolGameTablesFunctionLibrary, Log, All);

/**
 * 
 */
UCLASS(Blueprintable)
class OLDSCHOOLRPG_API UGameTablesFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UGameTablesFunctionLibrary();
	// some constants
	UPROPERTY(BlueprintReadOnly, Category="Constants")
	int32 BaseArmourClass = 9;
	UPROPERTY(BlueprintReadOnly, Category="Constants")
	int32 DefaultMovementRate = 120;
	UFUNCTION(BlueprintCallable, Category="Constants")
	static int32 GetCoinLimit();
	UFUNCTION(BlueprintCallable, Category="Constants")
	int32 GetArmourAC(EArmour::Armour Armour);
	// data table functions
	UFUNCTION(BlueprintCallable, Category="Initialization")
	UDataTable* GetAvailableEquipment();
	UFUNCTION(BlueprintCallable, Category="Initialization")
	UDataTable* GetWeaponStats();
	UFUNCTION(BlueprintCallable, Category="Initialization")
	UDataTable* GetClassProgressionDataTable(EClasses::Class CharacterClass);
	UFUNCTION(BlueprintCallable, Category="Initialization")
	UDataTable* GetClassSpellsDataTable(EClasses::Class CharacterClass);
	// attribute functions
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attribute Modifiers")
	int32 GetStrengthModifier(int32 BaseValue);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attribute Modifiers")
	int32 GetDexterityModifier(int32 BaseValue);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attribute Modifiers")
	static int32 GetConstitutionModifier(int32 BaseValue);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attribute Modifiers")
	int32 GetIntelligenceModifier(int32 BaseValue);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attribute Modifiers")
	int32 GetWisdomModifier(int32 BaseValue);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attribute Modifiers")
	int32 GetCharismaModifier(int32 BaseValue);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attribute Modifiers")
	int32 InitiativeModifier(int32 BaseValue);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attribute Modifiers")
	static int32 GetAttributeExperienceModifier(int32 AbilityValue);
	UFUNCTION(BlueprintPure, BlueprintPure, Category="Attribute Modifiers")
	static uint8 GetMaxRetainers(int32 BaseCharismaValue);
	// class properties functions
	UFUNCTION(BlueprintCallable, Category="Class Properties")
	FClassProperties GetClassProperties(EClasses::Class Class);
	// race properties functions
	UFUNCTION(BlueprintCallable, Category="Class Properties")
	FRaceProperties GetRaceProperties(ERaces::Race Race);
	// equipment functions
	UFUNCTION(BlueprintCallable, Category="Equipment")
	TArray<TEnumAsByte<ECharacterStates::State>> GetItemCharacterStates(FEquipment &Item);
protected:
	UFUNCTION()
	bool LoadRacePropertiesDataTable();
	bool LoadClassPropertiesDataTable();
	bool LoadCoinConversionDataTable();
	bool LoadEquipmentDataTable();
	bool LoadWeaponStatsDataTable();
	bool LoadClassProgressionDataTable(EClasses::Class SelectedClass);
	UPROPERTY()
	UDataTable* ClassPropertiesDataTable;
	UPROPERTY()
	UDataTable* RacePropertiesDataTable;
	UPROPERTY()
	UDataTable* CoinConversionDataTable;
	UPROPERTY()
	UDataTable* EquipmentDataTable;
	UPROPERTY()
	UDataTable* WeaponCombatStatsDataTable;
	UPROPERTY()
	UDataTable* CharacterProgressionDataTable;;
	static uint8 GetAttributeRange(uint8 BaseAttributeValue); 
	static int32 GetDefaultAttributeModifier(int32 BaseValue);
	static TArray<FString> GetCSVFile(FString Path);
	static EClasses::Class GetClassFromFString(FString DesiredClass);
	static ERaces::Race GetRaceFromString(FString DesiredRace);
	static ECoins::Coin GetCoinFromString(FString DesiredCoin);
	static EEquipmentType::Type GetEquipmentTypeFromString(FString DesiredEquipment);
	inline static int32 MaxCoins = 200; // max char encumbrance by default
	inline static TArray<uint8> MaxRetainers {1, 2, 3, 4, 5, 6, 7};
	inline static TArray<int8> BaseModifiers {-3, -2, -1, 0, 1, 2, 3};	
	inline static TArray<int8> NpcReactions {-2, -1, -1, 0, 1, 1, 2};
	
};
