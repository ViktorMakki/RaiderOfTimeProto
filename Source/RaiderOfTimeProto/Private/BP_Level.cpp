// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Level.h"
#include "BP_Maze.h"

// Sets default values
ABP_Level::ABP_Level()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

bool IsDoor(const FPathSegment& segment) {
  const auto& directions = segment.directionsAvailable;
	if ( directions.Num() == 2) {
    return (static_cast<int32>(directions[0]) + 2) % 4 == 
						static_cast<int32> (directions[1]) ? 
      true : false;
	}
        return false;
}

TArray<FPuzzleConstructionData> GetPuzzleConstructionDatas(const TArray<FPathSegment>& path, const ABP_Maze* maze, int32 puzzleCount)
{
  if (puzzleCount == 0) return {};

  TArray<FPuzzleConstructionData> result;
  const int32 length = path.Num();
  const int32 padding = 2;
  const int32 minDistance = (length / puzzleCount) - 2;
  for (size_t i = 0, count = 0; i < path.Num(); i++) {

  }
  return {};
}

void ABP_Level::Construct()
{
 /* if (!mazeType) return;

  ABP_Maze* maze = static_cast<ABP_Maze*>(GetWorld()->SpawnActor(mazeType));
  maze->GenerateMaze();

  const TArray<FPuzzleConstructionData> puzzleInputDatas =
      GetPuzzleConstructionDatas(maze->GetGoalPath(), maze, puzzleCount);

  for (const auto& startData : puzzleInputDatas) {
    TArray<UClass*> tempPuzzleTypes = availablePuzzles;
    bool done = false;
    while (!done) {
      if (tempPuzzleTypes.IsEmpty())
        break;
			const int32 randomIt = FMath::RandRange(0, tempPuzzleTypes.Num() - 1);
      done = static_cast<ABP_Puzzle*>(
                 GetWorld()->SpawnActor(tempPuzzleTypes[randomIt]))
                 ->Construct(startData);
			tempPuzzleTypes.RemoveAt(randomIt);
    }
  }*/
}
