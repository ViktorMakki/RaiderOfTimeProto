// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Generator.h"
#include "TileMap.h"

#include "TrapGenerator.generated.h"


UENUM(BlueprintType)
enum class TrapSpase : uint8 {
  WAY1 = 0 UMETA(DisplayName = "WAY1"),
  WAY2 = 1 UMETA(DisplayName = "WAY2"),
  WAY3 = 2 UMETA(DisplayName = "WAY3"),
  WAY4 = 3 UMETA(DisplayName = "WAY4"),
  TURN = 4 UMETA(DisplayName = "TURN")
};

USTRUCT(BlueprintType)
struct FTrap {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<UClass*> trapTypes;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TrapSpase requiredSpace;
};
/**
 * Generates traps 
 */
UCLASS(Blueprintable)
class RAIDEROFTIMEPROTO_API ATrapGenerator : public AGenerator
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	ATileMap* tileMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTrap> trapTypes;

  virtual void Destruct() override;

  virtual void Construct() override;
        
};
