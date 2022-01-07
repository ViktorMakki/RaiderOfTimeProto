// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "BP_Maze.h"

#include "TrapGenerator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RAIDEROFTIMEPROTO_API UTrapGenerator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//returns the generated objects
 UFUNCTION(BlueprintCallable)
 static TArray<AActivable*> GenerateTraps(ABP_Maze* maze, const TArray<FMazeTrap>& traps);
};
