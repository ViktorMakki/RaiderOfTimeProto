// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Puzzle.h"

// Sets default values
ABP_Puzzle::ABP_Puzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

bool ABP_Puzzle::Construct(const FPuzzleConstructionData& inputData)
{
  return false;
}


