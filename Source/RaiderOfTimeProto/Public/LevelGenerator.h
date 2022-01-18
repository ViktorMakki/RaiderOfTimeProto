// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generator.h"
#include "SymbolRule.h"
#include "LevelGenerator.generated.h"

//Called when everything is already spawned and setup for the level
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitLevel);

UCLASS()
class RAIDEROFTIMEPROTO_API ALevelGenerator : public AGenerator
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AGenerator*> generators;

	UPROPERTY(BlueprintAssignable)
  FInitLevel OnInitLevel;

	UFUNCTION(BlueprintCallable)
  static AActor* GetLevelGenerator();
	
	virtual void Destruct() override;

	virtual void Construct() override;
	
 private:
  static AActor* level;
};
