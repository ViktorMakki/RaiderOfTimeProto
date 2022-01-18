// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMap.h"
#include "UtilsLibrary.h"

// Sets default values
ATileMap::ATileMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATileMap::Create()
{
	Clear();
  SetSize(tileCount);
}

const FTile& ATileMap::GetConstTile(const FIntPoint& location) const
{
  return tiles[location.X].tiles[location.Y];
}

FTile& ATileMap::GetTile(const FIntPoint& location)
{
  return tiles[location.X].tiles[location.Y];
}

int32 ATileMap::GetTileTag(const FIntPoint& location) const
{
  return GetConstTile(location).tag;
}

void ATileMap::SetTileTag(const FIntPoint& location, int32 tag)
{
  GetTile(location).tag = tag;
}

const TArray<AActor*>& ATileMap::GetConstActorsAt(const FIntPoint& location) const
{
  return GetConstTile(location).actors;
}

TArray<AActor*>& ATileMap::GetActorsAt(const FIntPoint& location)
{
  return GetTile(location).actors;
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
AActor* ATileMap::SpawnActorAt(UClass* type, const FIntPoint& location, Direction4 direction)
{
  if (!type) return nullptr;
  const auto rotation = GetRotation(direction);
  const FVector relativePosition{location.X * tileSize, location.Y * tileSize, 0};
  const FVector position = GetTransform().GetLocation() + relativePosition;
  const auto newActor = GetWorld()->SpawnActor(type, &position, &rotation);
  newActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
  GetActorsAt(location).Add(newActor);
  return newActor;
}

void ATileMap::DestroyActorsAt(const FIntPoint& location)
{
  auto actors = GetActorsAt(location);
  for(auto* actor : actors) {
    actor->Destroy();
  }
  actors.Empty();
}

void ATileMap::ClearActors()
{
	const auto size = Size();
  if (size.SizeSquared() == 0) return;
  for (int32 x = 0; x < size.X; x++) {
  	for (int32 y = 0; y < size.Y; y++) {
      DestroyActorsAt({x, y});
  	}
  }
}

void ATileMap::Clear()
{
	ClearActors();
  tiles.Empty();
}

FIntPoint ATileMap::GetLocation(const AActor* actor) const
{
  if (!actor) return {-1, -1};
  const auto relativePosition = actor->GetActorLocation() - GetTransform().GetLocation();
  return {static_cast<int32>(relativePosition.X / tileSize),
          static_cast<int32>(relativePosition.Y / tileSize)};
}

FIntPoint ATileMap::Size() const
{
  if (tiles.IsEmpty()) return {0,0};
  return {tiles.Num(), tiles[0].tiles.Num()};
}

void ATileMap::SetSize(FIntPoint size)
{
	Clear();
  tiles.SetNum(size.X);
	for (int32 x = 0; x < size.X; x++) {
    tiles[x].tiles.SetNum(size.Y);
		for (int32 y = 0; y < size.Y; y++) {
      tiles[x].tiles[y].location = {x, y};
    }
  }
	tileCount = size;
}

FTile ATileMap::GetFirstTileByTag(int32 tag) const
{
  for (const auto& tileArray : tiles) {
     const auto& tile = Find<FTile>(tileArray.tiles,
         [&tag](const FTile& tile){
	         return tag == tile.tag;
         });
    if (tile.tag == tag) return tile;
  }
  return {};
}

