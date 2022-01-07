// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Level.h"
#include "BP_Maze.h"
#include "MazePath.h"
#include "TrapGenerator.h"

// Sets default values
ABP_Level::ABP_Level()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

//int32 GetNextDoorIndex(const TArray<FPathSegment>& path, const ABP_Maze* maze, int32 startIndex)
//{
//	for (int32 i = startIndex; i >= 0; i--) {
//		if (IsTypeOf(maze->GetTileType(path[i].location), MazeTileType::DOOR)) {
//			return i;
//		}
//	}
//	return 0;
//}
//TArray<FPuzzleConstructionData> GetPuzzleConstructionDatas(
//    ABP_Maze* maze, const TArray<int32>& puzzleDistanceMap) {
//  if (puzzleDistanceMap.Num() == 0) return {};
//
//  const auto goalPath = maze->path->GetPathToGoal();
//
//  TArray<FPuzzleConstructionData> result;
//  int32 index = GetNextDoorIndex(goalPath, maze, goalPath.Num() - 1);
//  //First door
//  const auto startSegment = goalPath[index];
//  const auto direction = SwapDirection(startSegment.directionToGoal);
//  result.Add({{startSegment.location, direction}, maze, puzzleDistanceMap[0]});
//
//	const int32 length = index;
//  const int32 padding = 2;
//  const int32 sizeOfPuzzleSegment = (length / (puzzleDistanceMap.Num())) - padding;
//
//  int32 start = index;
//  for (int32 puzzleIndex = 1; puzzleIndex < puzzleDistanceMap.Num(); puzzleIndex++) {
//    index = start - FMath::RandRange(padding, sizeOfPuzzleSegment);
//    if (index <= 0)
//      break;
//    index = GetNextDoorIndex(goalPath, maze, index);
//    const auto segment = goalPath[index];
//    result.Add({{segment.location, SwapDirection(segment.directionToGoal)}, maze, puzzleDistanceMap[puzzleIndex]});
//    start -= sizeOfPuzzleSegment;
//  }
//
//  return result;
//}

void ABP_Level::Construct()
{
  // 1. Generate maze
  // 2. Generate doors : first is the last door, then every double door, set tiles with doors to obsticle
  // 3. Generate traps :
  // 4. Generate rules for doors: map the doors to directed graph, set next doors opening conditions, and dilemma rules
  
#pragma region MazeGeneration
	if (!mazeType) return;
  maze = Cast<ABP_Maze, AActor>(GetWorld()->SpawnActor(mazeType))->GenerateMaze();
#pragma endregion

#pragma region TrapGeneration
  if (trapTypes.IsEmpty()) return;
  traps = UTrapGenerator::GenerateTraps(maze, trapTypes);
#pragma endregion

  /*const TArray<FPuzzleConstructionData> puzzleInputDatas =
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
      randomIt = (randomIt + 1) % tempPuzzleTypes.Num();
			tempPuzzleTypes.RemoveAt(randomIt);
    }
  }*/
}
