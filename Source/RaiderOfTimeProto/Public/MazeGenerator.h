// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generator.h"
#include "TileMap.h"
#include "MazeGenerator.generated.h"

USTRUCT(BlueprintType)
struct FMazeGeneratorInput {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  TArray<UClass*> wallTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  TArray<UClass*> pathTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  TArray<UClass*> gateTypes;

 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
 UClass* startType;

 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
 UClass* goalType;

 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
 UClass* goalGateType;
};

/**
 * Generates the walls, paths, doors, start and goal actors
 * and sets up the tags in the tileMap
 */
UCLASS()
class RAIDEROFTIMEPROTO_API AMazeGenerator : public AGenerator
{
	GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  ATileMap* tileMap;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  FMazeGeneratorInput input;

  virtual void Destruct() override;
  
  virtual void Construct() override;
};
