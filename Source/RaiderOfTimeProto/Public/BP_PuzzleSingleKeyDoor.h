// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BP_Puzzle.h"
#include "BP_PuzzleSingleKeyDoor.generated.h"

/**
 * 
 */
UCLASS()
class RAIDEROFTIMEPROTO_API ABP_PuzzleSingleKeyDoor : public ABP_Puzzle
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* doorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* keyType;

protected:
	virtual bool ConstructPuzzle(const UMazePath* mazePath, ABP_Maze* maze) override;
};
