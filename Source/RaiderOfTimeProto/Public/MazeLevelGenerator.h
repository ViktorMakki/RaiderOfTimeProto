// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generator.h"
#include "MazeTileTagGenerator.h"
#include "MazeGenerator.h"
#include "SymbolGenerator.h"
#include "KeyGenerator.h"
#include "TrapGenerator.h"
#include "LevelGenerator.h"

#include "MazeLevelGenerator.generated.h"

/**
 * 
 */
UCLASS()
class RAIDEROFTIMEPROTO_API AMazeLevelGenerator : public AGenerator
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint mazeSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float tileSize = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSymbol> symbols;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTrap> traps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMazeTileGeneratorInput mazeSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMazeGeneratorInput mazeActorSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKeyGeneratorInput keyActorSettings;

	virtual void Construct() override;

	virtual void Destruct() override;
protected:
 void BeginPlay() override;
private:
	ATileMap* tileMap;
	AMazeTileTagGenerator* mazeTileGenerator;
	AMazeGenerator* mazeActorGenerator;
	ASymbolGenerator* gateSymbolGenerator;
  AKeyGenerator* keyGenerator;
  ATrapGenerator* trapGenerator;
  ASymbolGenerator* trapSymbolGenerator;
	ALevelGenerator* level;
};
