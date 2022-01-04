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

FRotator GetRotation(Direction4 direction) {
  switch (direction) {
    case Direction4::DOWN:
      return {0, 90, 0};
    case Direction4::LEFT:
      return {0, 0, 0};
    case Direction4::UP:
      return {0, -90, 0};
    case Direction4::RIGHT:
      return {0, 180, 0};
    default:
      return {};
  }
}

const TArray<FTileArray>& ABP_Maze::GetTiles() const
{
	return mazeData.tiles;
}

MazeTileType ABP_Maze::GetTileType(const FIntPoint& location) const
{
  return mazeData.tiles[location.X].tiles[location.Y].tile;
}

void ABP_Maze::SetTileType(const FIntPoint& location, MazeTileType type)
{
  mazeData.tiles[location.X].tiles[location.Y].tile = type;
}

ABP_Maze* ABP_Maze::GenerateMaze() {

	mazeData = UMazeGenerator::GenerateMaze(mazeConstructionData);

	//Init arrays
	actors.SetNum(mazeConstructionData.mazeWidth);
	for(auto& item : actors) {
    item.actors.SetNum(mazeConstructionData.mazeHeight);
	}

	//Spawn path and wall actors
	for (int32 x = 0; x < mazeConstructionData.mazeWidth; x++) {
          for (int32 y = 0; y < mazeConstructionData.mazeHeight; y++) {
			if(UMazeGenerator::IsTypeOf(mazeData.tiles[x].tiles[y].tile, MazeTileType::PATH)) {
				if (mazeData.tiles[x].tiles[y].tile == MazeTileType::GOAL ) {
					if (end == FIntPoint{0, 0}) {
            end = {x, y};
            SpawnActorAt(goalClass, end, {});
					}
				} else {
					SpawnActorAt(pathClass, FIntPoint{x, y}, {});
				}
			} else {
				SpawnActorAt(wallsClass, FIntPoint{x, y}, {});
			}
		}
	}

	//Set path
	path = UMazePath::Create(mazeData.tiles, end);
  const auto pathToGoal = path->GetPathToGoal();
  start = pathToGoal[0].location;
  GetActorsAt(start).Empty();
  SpawnActorAt(startClass, start, {});
  for (const auto& segment : pathToGoal) {
  	mazeData.tiles[segment.location.X].tiles[segment.location.Y].tile =
			mazeData.tiles[segment.location.X].tiles[segment.location.Y].tile | MazeTileType::PATHTOGOAL;
  }

	return this;
}

TArray<AActor*>& ABP_Maze::GetActorsAt(const FIntPoint& location)
{
	return actors[location.X].actors[location.Y].actors;
}

AActor* ABP_Maze::SpawnActorAt(UClass* type, const FIntPoint& location, Direction4 direction) {
  const auto rotation = GetRotation(direction);
  const FVector position{location.X * tileSize,
                         location.Y * tileSize, 0};
  const auto newActor = GetWorld()->SpawnActor(type, &position, &rotation);
  GetActorsAt(location).Add(newActor);
  return newActor;
}

void ABP_Maze::DebugGoalPath()
{
  auto pathToGoal = path->GetPathToGoal();
  for (const auto& segment : pathToGoal) {
		const auto rotation = GetRotation(segment.directionToGoal);
		const FVector location{segment.location.X * tileSize,segment.location.Y * tileSize, 0};
		GetWorld()->SpawnActor(debugClass, &location, &rotation);
	}
}
