


#include "GameTablesFunctionLibrary.h"

DEFINE_LOG_CATEGORY(LogOldSchoolGameTablesFunctionLibrary);

UGameTablesFunctionLibrary::UGameTablesFunctionLibrary()
{
	CsvLoader = CsvDataTableLoader();
	LoadRacePropertiesDataTable();
	LoadClassPropertiesDataTable();
	LoadCoinConversionDataTable();
	LoadWeaponStatsDataTable();
	LoadEquipmentDataTable();
}

int32 UGameTablesFunctionLibrary::GetCoinLimit()
{
	return MaxCoins;
}

int32 UGameTablesFunctionLibrary::GetArmourAC(EArmour::Armour Armour)
{
	switch (Armour)
	{
		case EArmour::Leather:
			return BaseArmourClass - 2;
		case EArmour::Chainmail:
			return BaseArmourClass - 4;
		case EArmour::PlateMail:
			return BaseArmourClass - 6;
		case EArmour::Shield:
			return BaseArmourClass - 1;
		default:
			return BaseArmourClass;
	}
}

UDataTable* UGameTablesFunctionLibrary::GetAvailableEquipment()
{
	if (EquipmentDataTable == nullptr)
	{
		LoadEquipmentDataTable();
	}

	return EquipmentDataTable;
}

UDataTable* UGameTablesFunctionLibrary::GetWeaponStats()
{
	if (WeaponCombatStatsDataTable == nullptr)
	{
		LoadWeaponStatsDataTable();
	}

	return WeaponCombatStatsDataTable;
}

UDataTable* UGameTablesFunctionLibrary::GetClassProgressionDataTable(EClasses::Class CharacterClass)
{
	LoadClassProgressionDataTable(CharacterClass);

	return CharacterProgressionDataTable;
}

UDataTable* UGameTablesFunctionLibrary::GetClassSpellsDataTable(EClasses::Class CharacterClass)
{
	const FString SelectedClass = StaticEnum<EClasses::Class>()->GetNameStringByValue(CharacterClass);
	FString Path = "/OldSchoolRPG/Content/Tables/CSV/Spells/" + SelectedClass + ".csv";
	UClass* DataTableClass = UDataTable::StaticClass();
	UDataTable* CharacterSpells = NewObject<UDataTable>(this, DataTableClass, FName(TEXT("CharacterSpells")));
	CharacterSpells->RowStruct = FSpell::StaticStruct();
	TArray<FString> CSVLines = GetCSVFile(Path);
	for (int i = 1; i < CSVLines.Num(); i++)
	{
		FSpell Row;
		FString aString = CSVLines[i];
		TArray<FString> stringArray = {};
		aString.ParseIntoArray(stringArray, TEXT(","), false);
		if (stringArray.Num() == 0){continue;}
		FString LineLabel = stringArray[0];
		if ((LineLabel.Len() == 0)  || LineLabel.StartsWith("\";") || LineLabel.StartsWith(";"))
		{
			continue;	// Skip comments or lines with no label
		}
		Row.Name = *stringArray[1];
		Row.Level = FCString::Atoi(*stringArray[2]);
		Row.IsReversed = FCString::ToBool(*stringArray[3]);
		Row.Classes.Add(CharacterClass);

		CharacterSpells->AddRow(FName(*stringArray[0]), Row);
	}

	return CharacterSpells;
}

uint8 UGameTablesFunctionLibrary::GetStrengthModifier(uint8 BaseValue)
{
	return GetDefaultAttributeModifier(BaseValue);
}

uint8 UGameTablesFunctionLibrary::GetDexterityModifier(uint8 BaseValue)
{
	return GetDefaultAttributeModifier(BaseValue);
}

uint8 UGameTablesFunctionLibrary::GetConstitutionModifier(uint8 BaseValue)
{
	
	return GetDefaultAttributeModifier(BaseValue);
}

uint8 UGameTablesFunctionLibrary::GetIntelligenceModifier(uint8 BaseValue)
{
	return GetDefaultAttributeModifier(BaseValue);
}

uint8 UGameTablesFunctionLibrary::GetWisdomModifier(uint8 BaseValue)
{
	return GetDefaultAttributeModifier(BaseValue);
}

uint8 UGameTablesFunctionLibrary::GetCharismaModifier(uint8 BaseValue)
{
	return GetDefaultAttributeModifier(BaseValue);
}

bool UGameTablesFunctionLibrary::LoadRacePropertiesDataTable()
{
	FCsvGameTable RaceCsvGameTable = FCsvGameTable("RaceAttributes.csv");
	UClass* DataTableClass = UDataTable::StaticClass();
	RacePropertiesDataTable = NewObject<UDataTable>(this, DataTableClass, FName(TEXT("RacePropertiesDataTable")));
	RacePropertiesDataTable->RowStruct = FRaceProperties::StaticStruct();
	TArray<FString> CSVLines = CsvLoader.GetCSVFileContent(RaceCsvGameTable);
	FRaceProperties Row;
	for (int i = 1; i < CSVLines.Num(); i++)
	{
		FString aString = CSVLines[i];
		TArray<FString> stringArray = {};
		aString.ParseIntoArray(stringArray, TEXT(";"), false);
		if (stringArray.Num() == 0){continue;}
		FString LineLabel = stringArray[0];
		if ((LineLabel.Len() == 0)  || LineLabel.StartsWith("\";") || LineLabel.StartsWith(";"))
		{
			continue;	// Skip comments or lines with no label
		}
		Row.Name = GetRaceFromString(stringArray[1]);
		Row.Description = *stringArray[2];
		Row.Requirements = *stringArray[3];
		Row.AbilityModifiers = *stringArray[4];
		Row.Languages = *stringArray[5];
		Row.ClassRestrictions = *stringArray[6];
		Row.Features = *stringArray[7];

		RacePropertiesDataTable->AddRow(FName(*stringArray[0]), Row);
	}
	
	return RacePropertiesDataTable != nullptr;
}

uint8 UGameTablesFunctionLibrary::GetAttributeRange(uint8 BaseAttributeValue)
{
	if (BaseAttributeValue <= 3)
	{
		return 0;
	}
	if (BaseAttributeValue <= 5)
	{
		return 1;
	}
	if (BaseAttributeValue <= 8)
	{
		return 2;
	}
	if (BaseAttributeValue <= 12)
	{
		return 3;
	}
	if (BaseAttributeValue <= 15)
	{
		return 4;
	}
	if (BaseAttributeValue <= 17)
	{
		return 5;
	}

	return 6;
}

uint8 UGameTablesFunctionLibrary::GetDefaultAttributeModifier(uint8 BaseValue)
{
	if (BaseValue <= 3)
	{
		return -3;
	}
	if (BaseValue <= 5)
	{
		return -2;
	}
	if (BaseValue <= 8)
	{
		return -1;
	}
	if (BaseValue <= 12)
	{
		return 0;
	}
	if (BaseValue <= 15)
	{
		return 1;
	}
	if (BaseValue <= 17)
	{
		return 2;
	}
	if (BaseValue <= 18)
	{
		return 3;
	}

	return 4; // max value just in case
}

uint8 UGameTablesFunctionLibrary::GetMaxRetainers(int32 BaseCharisma)
{
	return MaxRetainers[GetAttributeRange(BaseCharisma)];
}

TArray<FString> UGameTablesFunctionLibrary::GetCSVFile(FString Path)
{
	TArray<FString> Lines;
	FString CsvFile = FPaths::ProjectPluginsDir() + Path;
	if (FPaths::FileExists(CsvFile))
	{
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("File %s exists"), *CsvFile);		
		FFileHelper::LoadANSITextFileToStrings(*CsvFile, NULL, Lines);
	}

	return Lines;
}

bool UGameTablesFunctionLibrary::LoadClassProgressionDataTable(EClasses::Class Class)
{
	const FString SelectedClass = StaticEnum<EClasses::Class>()->GetNameStringByValue(Class);
	FString Path = "/OldSchoolRPG/Content/Tables/CSV/ClassProgression/" + SelectedClass + "Progression.csv";
	UClass* DataTableClass = UDataTable::StaticClass();
	CharacterProgressionDataTable = NewObject<UDataTable>(this, DataTableClass, FName(TEXT("WizardProgressionDataTable")));
	CharacterProgressionDataTable->RowStruct = FClassLevel::StaticStruct();
	TArray<FString> CSVLines = GetCSVFile(Path);
	for (int i = 1; i < CSVLines.Num(); i++)
	{
		FClassLevel Row;
		FString aString = CSVLines[i];
		TArray<FString> stringArray = {};
		aString.ParseIntoArray(stringArray, TEXT(","), false);
		if (stringArray.Num() == 0){continue;}
		FString LineLabel = stringArray[0];
		if ((LineLabel.Len() == 0)  || LineLabel.StartsWith("\";") || LineLabel.StartsWith(";"))
		{
			continue;	// Skip comments or lines with no label
		}
		Row.Level = FCString::Atoi(*stringArray[1]);
		Row.XP = FCString::Atoi(*stringArray[2]);
		Row.HD = *stringArray[3];
		Row.THAC0 = FCString::Atoi(*stringArray[4]);
		Row.SD = FCString::Atoi(*stringArray[5]);
		Row.SW = FCString::Atoi(*stringArray[6]);
		Row.SP = FCString::Atoi(*stringArray[7]);
		Row.SB = FCString::Atoi(*stringArray[8]);
		Row.SS = FCString::Atoi(*stringArray[9]);
		Row.S1 = FCString::Atoi(*stringArray[10]);
		Row.S2 = FCString::Atoi(*stringArray[11]);
		Row.S3 = FCString::Atoi(*stringArray[12]);
		Row.S4 = FCString::Atoi(*stringArray[13]);
		Row.S5 = FCString::Atoi(*stringArray[14]);

		CharacterProgressionDataTable->AddRow(FName(*stringArray[0]), Row);
	}

	return CharacterProgressionDataTable != nullptr;
}

TArray<TEnumAsByte<ECharacterStates::State>> UGameTablesFunctionLibrary::GetItemCharacterStates(FEquipment &Item)
{
	TArray<TEnumAsByte<ECharacterStates::State>> GrantedStates;
	switch (Item.Type)
	{
	case EEquipmentType::Ammunition:
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding no stat granted for %s."), *Item.InternalName);
		break;
	case EEquipmentType::Armour:
		GrantedStates.Add(ECharacterStates::HasArmourEquipped);
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding armour stat granted for %s."), *Item.InternalName);
		if (Item.FullName.Contains("shield"))
		{
			GrantedStates.Add(ECharacterStates::HasShieldEquipped);
			UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding shield stat granted for %s."), *Item.InternalName);
		}
		break;
	case EEquipmentType::Misc:
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding no stat granted for %s."), *Item.InternalName);
		break;
	case EEquipmentType::Weapon:
		GrantedStates.Add(ECharacterStates::HasWeaponEquipped);
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding weapon stat granted for %s."), *Item.InternalName);
		if (WeaponCombatStatsDataTable != nullptr)
		{
			FWeaponStats* WeaponStats = WeaponCombatStatsDataTable->FindRow<FWeaponStats>(FName(Item.InternalName), Item.InternalName, true);
			if (WeaponStats != nullptr && WeaponStats->Qualities.Contains(TEXT("missile"), ESearchCase::IgnoreCase))
			{
				UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding ranged weapon stat granted for %s."), *Item.InternalName);
				GrantedStates.Add(ECharacterStates::HasRangedWeaponEquipped);
			}
			if (WeaponStats != nullptr && WeaponStats->Qualities.Contains(TEXT("two-handed"), ESearchCase::IgnoreCase))
			{
				UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding two-handed weapon stat granted for %s."), *Item.InternalName);
				GrantedStates.Add(ECharacterStates::HasTwoHandedWeaponEquipped);
			}
			if (WeaponStats != nullptr && WeaponStats->Qualities.Contains(TEXT("slow"), ESearchCase::IgnoreCase))
			{
				UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding slow weapon stat granted for %s."), *Item.InternalName);
				GrantedStates.Add(ECharacterStates::HasSlowWeaponEquipped);
			}
			if (WeaponStats != nullptr && WeaponStats->Qualities.Contains(TEXT("blunt"), ESearchCase::IgnoreCase))
			{
				UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding blunt weapon stat granted for %s."), *Item.InternalName);
				GrantedStates.Add(ECharacterStates::HasBluntWeaponEquipped);
			}
			if (WeaponStats != nullptr && WeaponStats->Qualities.Contains(TEXT("reload"), ESearchCase::IgnoreCase))
			{
				UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding reload weapon stat granted for %s."), *Item.InternalName);
				GrantedStates.Add(ECharacterStates::HasReloadWeaponEquipped);
			}
			if (WeaponStats != nullptr && WeaponStats->Qualities.Contains(TEXT("splash"), ESearchCase::IgnoreCase))
			{
				UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding splash weapon stat granted for %s."), *Item.InternalName);
				GrantedStates.Add(ECharacterStates::HasReloadWeaponEquipped);
			}
			if (WeaponStats != nullptr && WeaponStats->Qualities.Contains(TEXT("charge"), ESearchCase::IgnoreCase))
			{
				UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding charge weapon stat granted for %s."), *Item.InternalName);
				GrantedStates.Add(ECharacterStates::HasChargeWeaponEquipped);
			}
			if (WeaponStats != nullptr && WeaponStats->Qualities.Contains(TEXT("brace"), ESearchCase::IgnoreCase))
			{
				UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding brace weapon stat granted for %s."), *Item.InternalName);
				GrantedStates.Add(ECharacterStates::HasBraceWeaponEquipped);
			}
		}
		break;
	case EEquipmentType::AdventuringGear:
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Adding no stat granted for %s."), *Item.InternalName);
		break;
	default: ;
	}

	return GrantedStates;
}

uint8 UGameTablesFunctionLibrary::InitiativeModifier(uint8 BaseValue)
{
	return BaseModifiers[GetAttributeRange(BaseValue)];
}

bool UGameTablesFunctionLibrary::LoadClassPropertiesDataTable()
{
	FString Path = "/OldSchoolRPG/Content/Tables/CSV/ClassAttributes.csv";
	UClass* DataTableClass = UDataTable::StaticClass();
	ClassPropertiesDataTable = NewObject<UDataTable>(this, DataTableClass, FName(TEXT("ClassAttributesDataTable")));
	ClassPropertiesDataTable->RowStruct = FClassProperties::StaticStruct();
	TArray<FString> CSVLines = GetCSVFile(Path);
	for (int i = 1; i < CSVLines.Num(); i++)
	{
		FClassProperties Row;
		FString aString = CSVLines[i];
		TArray<FString> stringArray = {};
		aString.ParseIntoArray(stringArray, TEXT(";"), false);
		if (stringArray.Num() == 0){continue;}
		FString LineLabel = stringArray[0];
		if ((LineLabel.Len() == 0))
		{
			continue;	// Skip comments or lines with no label
		}
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Loading class %s."), *stringArray[1]);
		Row.ClassName = GetClassFromFString(stringArray[1]);
		Row.Requirements = *stringArray[2];
		Row.PrimeRequisite = *stringArray[3];
		Row.HitDice = *stringArray[4];
		Row.MaxLevel = FCString::Atoi(*stringArray[5]);
		Row.Armour = *stringArray[6];
		Row.Weapons = *stringArray[7];
		Row.Languages = *stringArray[8];
		Row.Description = *stringArray[9];
		Row.SaveD = FCString::Atoi(*stringArray[10]);
		Row.SaveW = FCString::Atoi(*stringArray[11]);
		Row.SaveP = FCString::Atoi(*stringArray[12]);
		Row.SaveB = FCString::Atoi(*stringArray[13]);
		Row.SaveS = FCString::Atoi(*stringArray[14]);
		Row.THAC0 = FCString::Atoi(*stringArray[15]);
		Row.ClassSkills = *stringArray[16];
		Row.ClassFeatures = *stringArray[17];

		ClassPropertiesDataTable->AddRow(FName(*stringArray[0]), Row);
	}
	
	return ClassPropertiesDataTable != nullptr;
}

bool UGameTablesFunctionLibrary::LoadCoinConversionDataTable()
{
	FString Path = "/OldSchoolRPG/Content/Tables/CSV/CoinConversion.csv";
	UClass* DataTableClass = UDataTable::StaticClass();
	CoinConversionDataTable = NewObject<UDataTable>(this, DataTableClass, FName(TEXT("CoinConversionDataTable")));
	CoinConversionDataTable->RowStruct = FCoinConversion::StaticStruct();
	TArray<FString> CSVLines = GetCSVFile(Path);
	for (int i = 1; i < CSVLines.Num(); i++)
	{
		FCoinConversion Row;
		FString aString = CSVLines[i];
		TArray<FString> stringArray = {};
		aString.ParseIntoArray(stringArray, TEXT(";"), false);
		if (stringArray.Num() == 0){continue;}
		FString LineLabel = stringArray[0];
		if ((LineLabel.Len() == 0))
		{
			continue;	// Skip comments or lines with no label
		}
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Loading coin conversion for %s."), *stringArray[0]);
		Row.CoinName = GetCoinFromString(stringArray[0]);
		Row.Platinum = FCString::Atoi(*stringArray[1]);
		Row.Gold = FCString::Atoi(*stringArray[2]);
		Row.Electrum = FCString::Atoi(*stringArray[3]);
		Row.Silver = FCString::Atoi(*stringArray[4]);
		Row.Copper = FCString::Atoi(*stringArray[5]);
		CoinConversionDataTable->AddRow(FName(*stringArray[0]), Row);
	}

	return CoinConversionDataTable != nullptr;
}

bool UGameTablesFunctionLibrary::LoadEquipmentDataTable()
{
	FString Path = "/OldSchoolRPG/Content/Tables/CSV/Equipment.csv";
	UClass* DataTableClass = UDataTable::StaticClass();
	EquipmentDataTable = NewObject<UDataTable>(this, DataTableClass, FName(TEXT("EquipmentDataTable")));
	EquipmentDataTable->RowStruct = FEquipment::StaticStruct();
	TArray<FString> CSVLines = GetCSVFile(Path);
	for (int i = 1; i < CSVLines.Num(); i++)
	{
		FEquipment Row;
		FString aString = CSVLines[i];
		TArray<FString> stringArray = {};
		aString.ParseIntoArray(stringArray, TEXT(";"), false);
		if (stringArray.Num() == 0){continue;}
		FString LineLabel = stringArray[0];
		if ((LineLabel.Len() == 0))
		{
			continue;	// Skip comments or lines with no label
		}
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Loading equipment for %s."), *stringArray[0]);
		Row.InternalName = *stringArray[0];
		Row.FullName = *stringArray[1];
		Row.Type = GetEquipmentTypeFromString(stringArray[2]);
		Row.Cost = FCString::Atod(*stringArray[3]);
		Row.Description = FText::FromString(*stringArray[4]);
		Row.Weight = FCString::Atoi(*stringArray[5]);
			
		Row.GrantStatesWhenEquipped = GetItemCharacterStates(Row);
		EquipmentDataTable->AddRow(FName(*stringArray[0]), Row);
	}

	return EquipmentDataTable != nullptr;
}

bool UGameTablesFunctionLibrary::LoadWeaponStatsDataTable()
{
	FString Path = "/OldSchoolRPG/Content/Tables/CSV/WeaponCombatStats.csv";
	UClass* DataTableClass = UDataTable::StaticClass();
	WeaponCombatStatsDataTable = NewObject<UDataTable>(this, DataTableClass, FName(TEXT("WeaponCombatStatsDataTable")));
	WeaponCombatStatsDataTable->RowStruct = FWeaponStats::StaticStruct();
	TArray<FString> CSVLines = GetCSVFile(Path);
	for (int i = 1; i < CSVLines.Num(); i++)
	{
		FWeaponStats Row;
		FString aString = CSVLines[i];
		TArray<FString> stringArray = {};
		aString.ParseIntoArray(stringArray, TEXT(";"), false);
		if (stringArray.Num() == 0){continue;}
		FString LineLabel = stringArray[0];
		if ((LineLabel.Len() == 0))
		{
			continue;	// Skip comments or lines with no label
		}
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Loading weapon stats for %s."), *stringArray[0]);
		Row.Name = *stringArray[1];
		Row.Damage = *stringArray[2];
		Row.Qualities = *stringArray[3];
		WeaponCombatStatsDataTable->AddRow(FName(*stringArray[0]), Row);
	}

	return WeaponCombatStatsDataTable != nullptr;
}

FClassProperties UGameTablesFunctionLibrary::GetClassProperties(EClasses::Class Class)
{
	const FString SelectedClass = StaticEnum<EClasses::Class>()->GetNameStringByValue(Class);
	UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Selected %s"), *SelectedClass);
	if (SelectedClass.IsEmpty())
	{
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Error, TEXT("Missing selected class when selecting class properties."));
		std::exit(1);
	}
	if (ClassPropertiesDataTable == nullptr)
	{
		LoadClassPropertiesDataTable();
	}
	FClassProperties *Row = ClassPropertiesDataTable->FindRow<FClassProperties>(*SelectedClass, *SelectedClass, true);
	if (Row == nullptr)
	{
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Error, TEXT("Missing row for %s."), *SelectedClass);
		std::exit(1);
	}
	
	return *Row;
}

EClasses::Class UGameTablesFunctionLibrary::GetClassFromFString(FString DesiredClass)
{
	
	if (DesiredClass == "Cleric")
	{
		return EClasses::Cleric;
	}
	if (DesiredClass == "Fighter")
	{
		return EClasses::Fighter;
	}
	if (DesiredClass == "Wizard")
	{
		return EClasses::Wizard;
	}
	return EClasses::Thief;
}

ERaces::Race UGameTablesFunctionLibrary::GetRaceFromString(FString DesiredRace)
{
	if (DesiredRace == "Dwarf")
	{
		return ERaces::Dwarf;
	}
	if (DesiredRace == "Elf")
	{
		return ERaces::Elf;
	}
	if (DesiredRace == "Halfling")
	{
		return ERaces::Halfling;
	}
	return ERaces::Human;
}

ECoins::Coin UGameTablesFunctionLibrary::GetCoinFromString(FString DesiredCoin)
{
	if (DesiredCoin == "Platinum")
	{
		return ECoins::Platinum;
	}
	if (DesiredCoin == "Gold")
	{
		return ECoins::Gold;
	}
	if (DesiredCoin == "Electrum")
	{
		return ECoins::Electrum;
	}
	if (DesiredCoin == "Silver")
	{
		return ECoins::Silver;
	}
	return ECoins::Copper;
}

EEquipmentType::Type UGameTablesFunctionLibrary::GetEquipmentTypeFromString(FString DesiredEquipment)
{
	if (DesiredEquipment == "AdventuringGear")
	{
		return EEquipmentType::AdventuringGear;
	}
	if (DesiredEquipment == "Weapon")
	{
		return EEquipmentType::Weapon;
	}
	if (DesiredEquipment == "Armour")
	{
		return EEquipmentType::Armour;
	}
	if (DesiredEquipment == "Ammunition")
	{
		return EEquipmentType::Ammunition;
	}
	return EEquipmentType::Misc;
}

FRaceProperties UGameTablesFunctionLibrary::GetRaceProperties(ERaces::Race Race)
{
	const FString SelectedRace = StaticEnum<ERaces::Race>()->GetNameStringByValue(Race);
	UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Log, TEXT("Selected %s"), *SelectedRace);
	if (SelectedRace.IsEmpty())
	{
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Error, TEXT("Missing selected race."));
		std::exit(1);
	}
	if (RacePropertiesDataTable == nullptr)
	{
		LoadRacePropertiesDataTable();
	}
	FRaceProperties *Row = RacePropertiesDataTable->FindRow<FRaceProperties>(*SelectedRace, *SelectedRace, true);
	if (Row == nullptr)
	{
		UE_LOG(LogOldSchoolGameTablesFunctionLibrary, Error, TEXT("Missing row for %s."), *SelectedRace);
		std::exit(1);
	}
	
	return *Row;
}

int32 UGameTablesFunctionLibrary::GetAttributeExperienceModifier(int32 AbilityValue)
{
	int32 Modifier = -20;
	if (AbilityValue >= 6)
	{
		Modifier = -10;
	}	
	if (AbilityValue >= 9)
	{
		Modifier = 0;
	}
	if (AbilityValue >= 13)
	{
		Modifier = 5;
	}
	if (AbilityValue >= 16)
	{
		Modifier = 10;
	}	

	return Modifier;
}