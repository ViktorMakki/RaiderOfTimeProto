// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Level.h"
#include "BP_Maze.h"
#include "MazePath.h"

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

int32 GetNextDoorIndex(const TArray<FPathSegment>& path, int32 startIndex)
{
	for (int32 i = startIndex; i >= 0; i--) {
		if (IsDoor(path[i])) {
			return i;
		}
	}
	return 0;
}
TArray<FPuzzleConstructionData> GetPuzzleConstructionDatas(
    ABP_Maze* maze, const TArray<int32>& puzzleDistanceMap)
{
  const UMazePath path(maze->GetTiles(), maze->end);
  if (puzzleDistanceMap.Num() == 0) return {};

  const auto goalPath = path.GetPathToGoal();

  TArray<FPuzzleConstructionData> result;
  int32 index = GetNextDoorIndex(goalPath, goalPath.Num() - 1);
  //First door
  const auto startSegment = goalPath[index];
  const auto direction = static_cast<Direction4>((static_cast<int32>(startSegment.directionToGoal) + 2) % 4);
  result.Add({{startSegment.location, direction}, maze, puzzleDistanceMap[0]});

	const int32 length = index;
  const int32 padding = 2;
  const int32 sizeOfPuzzleSegment = (length / (puzzleDistanceMap.Num() - 1)) - padding;

  int32 start = index;
  for (int32 puzzleIndex = 1; puzzleIndex < puzzleDistanceMap.Num(); puzzleIndex++) {
    index = start + FMath::RandRange(padding, sizeOfPuzzleSegment);
    index = GetNextDoorIndex(goalPath, index);
    const auto segment = goalPath[index];
    result.Add({{segment.location, direction}, maze, puzzleDistanceMap[puzzleIndex]});
    start += sizeOfPuzzleSegment;
  }

  return result;
}

void ABP_Level::Construct()
{
 if (!mazeType) return;

  ABP_Maze* maze =
     Cast<ABP_Maze, AActor>(GetWorld()->SpawnActor(mazeType))->GenerateMaze();

  const TArray<FPuzzleConstructionData> puzzleInputDatas =
      GetPuzzleConstructionDatas(maze, puzzleDistanceMap);

  for (const auto& startData : puzzleInputDatas) {
    TArray<UClass*> tempPuzzleTypes = availablePuzzles;
    bool done = false;
  	int32 randomIt = FMath::RandRange(0, tempPuzzleTypes.Num() - 1);
    while (!done) {
      if (tempPuzzleTypes.IsEmpty())
        break;
      done = Cast<ABP_Puzzle, AActor>(
                 GetWorld()->SpawnActor(tempPuzzleTypes[randomIt]))
                 ->Construct(startData);
			tempPuzzleTypes.RemoveAt(randomIt);
      randomIt = (randomIt + 1) % tempPuzzleTypes.Num();
    }
  }
}
