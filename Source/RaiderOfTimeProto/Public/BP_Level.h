// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Puzzle.h"
#include "BP_Level.generated.h"

UCLASS()
class RAIDEROFTIMEPROTO_API ABP_Level : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Level();

	UFUNCTION(BlueprintCallable)
	void Construct();

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UClass* mazeType;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<FMazeTrap> trapTypes;
private:
  ABP_Maze* maze;
 TArray<ABP_Obsticle*> traps;
};
