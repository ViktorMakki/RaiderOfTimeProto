// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"

#include "MazePath.h"
#include "UtilsLibrary.h"

void AMazeGenerator::Destruct()
{
  if (!tileMap) return;
	tileMap->ClearActors();
}

void SpawnWithRandomDirection(ATileMap* tileMap, const FIntPoint& location, const TArray<UClass*>& types)
{
  const auto type = UUtilsLibrary::GetRandomType(types);
  if (!type) return;
  tileMap->SpawnActorAt(type, location, UUtilsLibrary::GetRandomDirection());
}

void SpawnSingleWithRandomPathDirection(ATileMap* tileMap, const FIntPoint& location, UClass* type)
{
  if (!type) return;
  tileMap->SpawnActorAt(type, location, UUtilsLibrary::GetRandomPathDirection(tileMap, location));
}

void SpawnWithRandomPathDirection(ATileMap* tileMap,
                                        const FIntPoint& location,
                                        const TArray<UClass*>& types)
{
  const auto type = UUtilsLibrary::GetRandomType(types);
  if (!type) return;
  tileMap->SpawnActorAt(type, location, UUtilsLibrary::GetRandomPathDirection(tileMap, location));
}



void AMazeGenerator::Construct()
{
  if (!tileMap) return;
  Destruct();
  const auto size = tileMap->Size();
  bool isGoalSpawned = false;
  for (int32 x = 0; x < size.X; x++) {
    for (int32 y = 0; y < size.Y; y++) {
      auto tile = tileMap->GetTile({x, y});

      switch (static_cast<MazeTileType>(tile.tag)) {
        case MazeTileType::PATH:
          SpawnWithRandomDirection(tileMap, {x, y}, input.pathTypes);
          break;
      case MazeTileType::START:
          if (input.startType)
            tileMap->SpawnActorAt(input.startType, {x, y},
                                  UUtilsLibrary::GetRandomDirection());
          break;
        case MazeTileType::GOAL:
          if(!isGoalSpawned) {
            isGoalSpawned = true;
            if (input.goalType) tileMap->SpawnActorAt(input.goalType, {x, y}, Direction4::DOWN);
          }
          break;
        case MazeTileType::GATE:
          SpawnWithRandomPathDirection(tileMap, {x, y}, input.gateTypes);
          break;
        case MazeTileType::GOALGATE:
          SpawnSingleWithRandomPathDirection(tileMap, {x, y}, input.goalGateType);
          break;
        case MazeTileType::WALL:
          SpawnWithRandomDirection(tileMap, {x, y}, input.wallTypes);
          break;
        default:;
      }
    }
  }
}