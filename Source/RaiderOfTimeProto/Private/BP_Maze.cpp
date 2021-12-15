// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Maze.h"
#include "MazeTypes.h"
#include "MazePath.h"

// Sets default values
ABP_Maze::ABP_Maze()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABP_Maze::GenerateMaze()
{
	mazeData = UMazeGenerator::GenerateMaze(mazeConstructionData);
	actors.SetNum(mazeConstructionData.mazeWidth);
	for(auto& item : actors) {
    item.actors.SetNum(mazeConstructionData.mazeHeight);
	}

	for (int32 x = 0; x < mazeConstructionData.mazeWidth; x++) {
          for (int32 y = 0; y < mazeConstructionData.mazeHeight; y++) {
			const FVector location{ x * tileSize, y * tileSize, 0 };
			if(UMazeGenerator::IsTypeOf(mazeData.tiles[x].tiles[y].tile, MazeTileType::PATH)) {
				if (mazeData.tiles[x].tiles[y].tile == MazeTileType::GOAL && end == FIntPoint{0,0}) {
					end = {x, y};
				}
				const auto actor = GetWorld()->SpawnActor(pathClass, &location);
				actors[x].actors[y].actors.Add(actor);
			} else {
				const auto actor = GetWorld()->SpawnActor(wallsClass, &location);
				actors[x].actors[y].actors.Add(actor);
			}
		}
	}
}

TArray<AActor*>& ABP_Maze::GetActorsAt(const FIntPoint& location)
{
	return actors[location.X].actors[location.Y].actors;
}

FRotator GetRotation(Direction4 direction)
{
	switch (direction) {
	case Direction4::DOWN: 
		return {0,90,0};
	case Direction4::LEFT:
          return {0, 0, 0};
	case Direction4::UP: 
          return {0, -90, 0};
	case Direction4::RIGHT:
          return {0, 180, 0};
	default: return {} ;
	}
}

void ABP_Maze::DebugGoalPath()
{
  const MazePath mazePath{mazeData.tiles, end};
  auto path = mazePath.GetPathToGoal();
	for (const auto& segment : path) {
		const auto rotation = GetRotation(segment.directionToGoal);
		const FVector location{segment.location.X * tileSize,segment.location.Y * tileSize, 0};
		GetWorld()->SpawnActor(debugClass, &location, &rotation);
	}
}
