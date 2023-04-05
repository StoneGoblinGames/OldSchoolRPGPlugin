// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterActorComponent.h"

DEFINE_LOG_CATEGORY(LogOldSchoolRPGCharacterComponent);

// Sets default values for this component's properties
UBaseCharacterActorComponent::UBaseCharacterActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseCharacterActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseCharacterActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseCharacterActorComponent::InitializeCharacter(FCharacterValues Values)
{
	Name = Values.Name;
	Race = Values.Race;
	Class = Values.Class;
	Background = Values.Background;
	Alignment = Values.Alignment;
	PrimeRequisite = Values.PrimeRequisite;
	AttackRoll = Values.AttackRoll;
	DeathSave = Values.DeathSave;
	WandSave = Values.WandSave;
	ParalysisSave = Values.ParalysisSave;
	BreathSave = Values.BreathSave;
	SpellSave = Values.SpellSave;
	Level = Values.Level;
	Strength = Values.Strength;
	Dexterity = Values.Dexterity;
	Constitution = Values.Constitution;
	Intelligence = Values.Intelligence;
	Wisdom = Values.Wisdom;
	Charisma = Values.Charisma;
	ArmorClass = Values.ArmorClass;
	Initiative = Values.Initiative;
	Speed = Values.Speed;
	HitPoints = Values.HitPoints;
	if (Values.HitPoints == 0)
	{
		HitPoints = RollHitPoints(Values.HitDice);
	}	
	HitDice = Values.HitDice;
	Equipment = Values.Equipment;
	Features = Values.Features;
	Spells = Values.Spells;
	FCoinTreasure InitialCoins;
	InitialCoins.Amount = Values.InitialGold;
	InitialCoins.Coin = ECoins::Gold;
	AddCoins(InitialCoins);
	CharacterProgression = Values.CharacterProgression;
}

int32 UBaseCharacterActorComponent::AddExperience(int32 BaseValue, bool PrimeRequisiteBonus)
{
	int32 Bonus = 0;
	if (PrimeRequisiteBonus)
	{
		Bonus = (BaseValue * GetPrimeRequisiteXPModifier() / 100);
	}
	int32 Amount = Bonus + BaseValue;
	Experience += Amount;
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Added %d Experience"), Amount);
	FString NextLevelNumber = FString::FromInt(Level+1);
	FClassLevel *NextLevel = CharacterProgression->FindRow<FClassLevel>(*NextLevelNumber, *NextLevelNumber, true);
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Next level at %d"), NextLevel->XP);
	if (Experience >= NextLevel->XP)
	{
		UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Level up"));
		LevelUp();
	}
	return Experience;
}

int32 UBaseCharacterActorComponent::GetPrimeRequisiteXPModifier()
{
	int32 Value = 0;
	if (PrimeRequisite == "Strength")
	{
		Value = Strength;
	}
	if (PrimeRequisite == "Dexterity")
	{
		Value = Dexterity;
	}
	if (PrimeRequisite == "Constitution")
	{
		Value = Constitution;
	}
	if (PrimeRequisite == "Intelligence")
	{
		Value = Intelligence;
	}
	if (PrimeRequisite == "Wisdom")
	{
		Value = Wisdom;
	}
	if (PrimeRequisite == "Charisma")
	{
		Value = Charisma;
	}

	return UGameTablesFunctionLibrary::GetAttributeExperienceModifier(Value);
}

bool UBaseCharacterActorComponent::LevelUp()
{
	FString NewLevelNumber = FString::FromInt(Level+1);
	FClassLevel *NextLevel = CharacterProgression->FindRow<FClassLevel>(*NewLevelNumber, *NewLevelNumber, true);
	Level += 1;
	AttackRoll = NextLevel->THAC0;
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("%s"), *FString::FromInt(AttackRoll));
	DeathSave = NextLevel->SD;
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("%s"), *FString::FromInt(DeathSave));
	WandSave = NextLevel->SW;
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("%s"), *FString::FromInt(WandSave));
	ParalysisSave = NextLevel->SP;
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("%s"), *FString::FromInt(ParalysisSave));
	BreathSave = NextLevel->SB;
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("%s"), *FString::FromInt(BreathSave));
	SpellSave = NextLevel->SS;
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("%s"), *FString::FromInt(SpellSave));
	HitDice = NextLevel->HD;
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("%s"), *HitDice);
	HitPoints = RollHitPoints(NextLevel->HD);
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("New hit points %d"), HitPoints);

	return true;
}

bool UBaseCharacterActorComponent::LevelUpAdvanced(FCharacterValues LevelUpValues)
{
	return true;
}

int32 UBaseCharacterActorComponent::GenerateRoll(FString DiceRoll)
{
	int32 Result = 0;

	DiceRoll = DiceRoll.ToLower();
	FString Delimiter = "d";
	TArray<FString> DiceRollParts;
	DiceRoll.ParseIntoArray(DiceRollParts, TEXT("d"));
	if (DiceRollParts.Num() > 1)
	{
		int32 NumDices = FCString::Atoi(*DiceRollParts[0]);
		int32 DiceSides = FCString::Atoi(*DiceRollParts[1]);
		if (NumDices > 0 && DiceSides > 0)
		{
			for (int32 i = 1; i < NumDices; i++)
			{
				int32 DiceResult = 1+ (rand() % DiceSides);
				UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Rolling 1d%s ..."), *FString::FromInt(DiceSides));
				UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Result is %s"), *FString::FromInt(DiceResult));
			}
		}
		
		UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("%sD%s"), *DiceRollParts[0], *DiceRollParts[1]);
	}	
	
	return Result;
}

uint8 UBaseCharacterActorComponent::RollHitPoints(FString HitPointsLiteral)
{
	uint8 HPModifier;
	bool AddConstitution = !HitPointsLiteral.Contains("*");
	if (AddConstitution)
	{
		HPModifier = UGameTablesFunctionLibrary::GetConstitutionModifier(Constitution);
	}
	else
	{
		TArray<FString> DiceRollParts;
		HitPointsLiteral = HitPointsLiteral.Replace(TEXT("*"), TEXT(""), ESearchCase::IgnoreCase);
		HitPointsLiteral.ParseIntoArray(DiceRollParts, TEXT("+"));
		HPModifier = FCString::Atoi(*DiceRollParts[1]);
		HitPointsLiteral = DiceRollParts[0];
	}

	return GenerateBasicRoll(HitPointsLiteral) + HPModifier;
}

int32 UBaseCharacterActorComponent::GenerateBasicRoll(FString DiceRoll)
{
	int32 Result = 0;
	int32 Modifier = 0;

	DiceRoll = DiceRoll.ToLower();
	TArray<FString> DiceRollParts;
	DiceRoll.ParseIntoArray(DiceRollParts, TEXT("+"));
	if (DiceRollParts.Num() > 1)
	{
		// we have a + roll
		Modifier = FCString::Atoi(*DiceRollParts[1]);
	}
	else
	{
		DiceRoll.ParseIntoArray(DiceRollParts, TEXT("-"));
		if (DiceRollParts.Num() > 1)
		{
			// we have a - roll
			Modifier = FCString::Atoi(*DiceRollParts[1]) * -1;
		}
	}
	TArray<FString> DiceRollParts2;
	DiceRollParts[0].ParseIntoArray(DiceRollParts2, TEXT("d"));
	if (DiceRollParts2.Num() > 1)
	{
		int32 NumDice = FCString::Atoi(*DiceRollParts2[0]);
		int32 DiceSides = FCString::Atoi(*DiceRollParts2[1]);
		UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Rolling %dD%d ."), NumDice, DiceSides);
		if (NumDice > 0 && DiceSides > 0)
		{
			for (int32 i = 1; i <= NumDice; i++)
			{
				int32 DiceResult = 1+ (rand() % DiceSides);
				Result += DiceResult;
				UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Rolled 1D%d, result %d ."), DiceSides, DiceResult);
			}
		}
	}
	UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Returning roll %d."), Result + Modifier);
	
	return Result + Modifier;
}

bool UBaseCharacterActorComponent::AddCoins(FCoinTreasure CoinsToAdd)
{
	int32 CoinLimit = UGameTablesFunctionLibrary::GetCoinLimit();
	int32 CarryingAmount = 0;
	bool CoinsAdded = false;
	// check that character can add those coins
	for (auto &Element : Coins)
	{
		const FString CoinName = StaticEnum<ECoins::Coin>()->GetNameStringByValue(Element.Key);
		UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Carrying %d %s coins."), Element.Value, *CoinName);
		CarryingAmount += Element.Value;
	}
	if (CarryingAmount + CoinsToAdd.Amount <= CoinLimit)
	{
		UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Can get all coins"));
		// find coin type and add amount
		if (Coins.Contains(CoinsToAdd.Coin))
		{
			int32 *ExistingAmount = Coins.Find(CoinsToAdd.Coin);
			int32 NewTotal = *ExistingAmount + CoinsToAdd.Amount;
			Coins.Emplace(CoinsToAdd.Coin, NewTotal);
		}
		else
		{
			// add new type of coin
			Coins.Emplace(CoinsToAdd.Coin, CoinsToAdd.Amount);
		}
	}
	else
	{
		UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Cannot get all coins"));
	}
	for (auto &Element : Coins)
	{
		const FString CoinName = StaticEnum<ECoins::Coin>()->GetNameStringByValue(Element.Key);
		UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Now carrying %d %s coins."), Element.Value, *CoinName);
	}

	return CoinsAdded;
}

uint8 UBaseCharacterActorComponent::GetRetainerLimit() const
{
	return 0; // UOldSchoolRPGTables::GetMaxRetainers(Charisma);
}

bool UBaseCharacterActorComponent::HasItemEquipped(EEquipmentSlot::Slot Slot)
{
	return EquipmentMap.Find(Slot) != nullptr;
}

void UBaseCharacterActorComponent::EquipItem(EEquipmentSlot::Slot Slot, FEquipmentItem Item)
{
	EquipmentMap.Emplace(Slot, Item); // place item on top of another of the same slot
	for (TEnumAsByte<ECharacterStates::State> &GrantingState : Item.GrantStates)
	{
		FCharacterState NewState;
		NewState.State = GrantingState;
		States.Add(NewState);
		FText EnumDisplayName = StaticEnum< ECharacterStates::State >()->GetDisplayNameTextByIndex( (int32) GrantingState );
		UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Added state %s"), *EnumDisplayName.ToString());
	}
}

FEquipmentItem UBaseCharacterActorComponent::UnEquipItem(EEquipmentSlot::Slot Slot)
{
	FEquipmentItem ItemToRemove;
	if (EquipmentMap.Find(Slot) != nullptr)
	{
		EquipmentMap.RemoveAndCopyValue(Slot, ItemToRemove);
		// remove all states granted by this item
		for (TEnumAsByte<ECharacterStates::State> &GrantingState : ItemToRemove.GrantStates)
		{
			for (auto ArrayState : States)
			{
				if (ArrayState.State == GrantingState)
				{
					States.Remove(ArrayState);
					FText EnumDisplayName = StaticEnum< ECharacterStates::State >()->GetDisplayNameTextByIndex( (int32) ArrayState.State );
					UE_LOG(LogOldSchoolRPGCharacterComponent, Log, TEXT("Removing state %s"), *EnumDisplayName.ToString());
					break; // we only remove one instance of each state
				}
			}
		}
	}
	
	return ItemToRemove;
}

