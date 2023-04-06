#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FClassLevel.generated.h"

USTRUCT(BlueprintType)
struct FClassLevel : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 Level {1};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 XP {0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString HD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 THAC0 {19};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 SD {20};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 SW {20};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 SP {20};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 SB {20};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 SS {20};	

	// spells per level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 S1 {0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 S2 {0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 S3 {0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 S4 {0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 S5 {0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 S6 {0};
};
