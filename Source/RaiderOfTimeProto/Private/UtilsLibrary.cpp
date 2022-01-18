// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilsLibrary.h"

#include "MazeTypes.h"

Direction4 UUtilsLibrary::GetRandomDirection()
{
  return static_cast<Direction4>(FMath::RandRange(0, 3));
}

TArray<Direction4> UUtilsLibrary::GetAvailableDirectionsInMaze(const FIntPoint& point, const ATileMap* maze)
{
  TArray<Direction4> result;
  if (IsTypeOf(static_cast<MazeTileType>(maze->GetTileTag(point + FIntPoint{0,1})),
      MazeTileType::PATH))
      result.Add(Direction4::UP);
  if (IsTypeOf(static_cast<MazeTileType>(maze->GetTileTag(point + FIntPoint{0, -1})),
      MazeTileType::PATH))
    result.Add(Direction4::DOWN);
  if (IsTypeOf(static_cast<MazeTileType>(maze->GetTileTag(point + FIntPoint{1, 0})),
      MazeTileType::PATH))
    result.Add(Direction4::RIGHT);
  if (IsTypeOf(static_cast<MazeTileType>(maze->GetTileTag(point + FIntPoint{-1, 0})),
     MazeTileType::PATH))
    result.Add(Direction4::LEFT);
  Shuffle(result);
  return result;
}

Direction4 UUtilsLibrary::GetRandomPathDirection(const ATileMap* tileMap, const FIntPoint& location)
{
  auto dirs = GetAvailableDirectionsInMaze(location, tileMap);
  if (dirs.IsEmpty()) return {};
  return dirs[FMath::RandRange(0, dirs.Num() - 1)];
}

UClass* UUtilsLibrary::GetRandomType(const TArray<UClass*> types)
{
  if (types.IsEmpty()) return nullptr;
  return types[FMath::RandRange(0, types.Num() - 1)];
}

ASymbolRule* UUtilsLibrary::GetSymbolRule(const UWorld* world, const FSymbol symbol)
{
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(world, ASymbolRule::StaticClass(),actors);
  return Cast<ASymbolRule>(Find<AActor>(actors, [&symbol](const AActor* actor) {
        const auto* symbolActor = Cast<ASymbolRule>(actor);
        if (!symbolActor) return false;
        return symbolActor->GetSymbol().id == symbol.id;
      }));
}
