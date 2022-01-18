// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generator.h"
#include "MazeTypes.h"
#include "SymbolRule.h"
#include "SymbolGenerator.generated.h"

/**
 * Generates SymbolRules for obsticles and wires them together
 */
UCLASS()
class RAIDEROFTIMEPROTO_API ASymbolGenerator : public AGenerator
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSymbol> symbolTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* obsticleType;
	
  virtual void Destruct() override;
	
  virtual void Construct() override;
};
