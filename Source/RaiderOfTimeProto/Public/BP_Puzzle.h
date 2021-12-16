// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Maze.h"
#include "MazePath.h"
#include "BP_Obsticle.h"

#include "BP_Puzzle.generated.h"

USTRUCT(BlueprintType)
struct FPuzzleStart
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite)
  FIntPoint startPoint;

	UPROPERTY(BlueprintReadWrite)
  Direction4 startdirection;
};

USTRUCT(BlueprintType)
struct FPuzzleConstructionData
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite)
  FPuzzleStart start;

  UPROPERTY(BlueprintReadWrite)
  ABP_Maze* maze;

	UPROPERTY(BlueprintReadWrite)
  int32 depth;
};

UCLASS()
class RAIDEROFTIMEPROTO_API ABP_Puzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Puzzle();
  
	UFUNCTION(BlueprintCallable)
	bool Construct(const FPuzzleConstructionData& inputData);

protected:

  UFUNCTION(BlueprintCallable)
	virtual bool ConstructPuzzle(const UMazePath* mazePath, ABP_Maze* maze);

	UFUNCTION(BlueprintCallable)
	static Direction4 SwapDirection(Direction4 direction);
};
