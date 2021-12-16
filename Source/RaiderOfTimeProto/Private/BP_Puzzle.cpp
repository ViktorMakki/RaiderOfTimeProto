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
  const UMazePath mazePath{UMazePath::GetSegmentsInDistance(
      inputData.maze->GetTiles(), inputData.start.startPoint,
      inputData.start.startdirection, inputData.depth)};

  return ConstructPuzzle(&mazePath, inputData.maze);
}

bool ABP_Puzzle::ConstructPuzzle(const UMazePath* mazePath, ABP_Maze* maze) {
  return false;
}

Direction4 ABP_Puzzle::SwapDirection(Direction4 direction)
{
  return static_cast<Direction4>((static_cast<int32>(direction) + 2) % 4);
}
