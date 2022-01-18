// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generator.h"
#include "TileMap.h"
#include "KeyGenerator.generated.h"

USTRUCT(BlueprintType)
struct FKeyGeneratorInput
{
	GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  TArray<UClass*> keyTypes;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  int32 keyCount;
};

/**
 * Generates Keys for the maze and wires them with the symbols
 */
UCLASS()
class RAIDEROFTIMEPROTO_API AKeyGenerator : public AGenerator
{
	GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  ATileMap* tileMap;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  FKeyGeneratorInput input;
  
  virtual void Destruct() override;
  
  virtual void Construct() override;
};
