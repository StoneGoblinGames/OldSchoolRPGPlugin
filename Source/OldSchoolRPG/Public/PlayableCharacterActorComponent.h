// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterActorComponent.h"
#include "PlayableCharacterActorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OLDSCHOOLRPG_API UPlayableCharacterActorComponent : public UBaseCharacterActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayableCharacterActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
