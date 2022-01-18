// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapGenerator.h"

#include <unordered_map>
#include <vector>

#include "Activable.h"
#include "MazeTypes.h"
#include "UtilsLibrary.h"

using TrapSpaceTiles = std::vector<std::vector<MazeTileType>>;

static std::unordered_map<TrapSpase, TrapSpaceTiles> GetTrapSpaceMap() {
  std::unordered_map<TrapSpase, std::vector<std::vector<MazeTileType>>> result;
  result[TrapSpase::WAY1] = {
      {MazeTileType::WALL, MazeTileType::WALL, MazeTileType::WALL},
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL},
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL}};

  result[TrapSpase::WAY2] = {
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL},
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL},
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL}};

  result[TrapSpase::WAY3] = {
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL},
      {MazeTileType::PATH, MazeTileType::PATH, MazeTileType::PATH},
      {MazeTileType::WALL, MazeTileType::WALL, MazeTileType::WALL}};

  result[TrapSpase::WAY4] = {
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL},
      {MazeTileType::PATH, MazeTileType::PATH, MazeTileType::PATH},
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL}};

  result[TrapSpase::TURN] = {
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::WALL},
      {MazeTileType::WALL, MazeTileType::PATH, MazeTileType::PATH},
      {MazeTileType::WALL, MazeTileType::WALL, MazeTileType::WALL}};

  return result;
}

void ReverseElementsRowWise(TrapSpaceTiles& matrix) {
  const int32 n = 3;
  for (int32 i = 0; i < n; ++i) {
    for (int32 j = 0; j < n / 2; ++j) {
      const MazeTileType temp = matrix[i][n - j - 1];
      matrix[i][n - j - 1] = matrix[i][j];
      matrix[i][j] = temp;
    }
  }
}
        
void Transpose(TrapSpaceTiles& matrix) {
  const int32 n = 3;
  for (int32 i = 0; i < n; ++i) {
    for (int32 j = i + 1; j < n; ++j) {
      const MazeTileType temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
  }
}

void RotateLeft(TrapSpaceTiles& tiles)
{
	Transpose(tiles);
  ReverseElementsRowWise(tiles);
}

bool IsFitableInDirection(const ATileMap* tileMap, const FIntPoint& start,
                          const TrapSpaceTiles& tiles)
{
  const auto size = tileMap->Size();
  for (int32 x = 0; x < 3; x++) {
    for (int32 y = 0; y < 3; y++) {
      FIntPoint currentLocation = start + FIntPoint{x, y};
      if (currentLocation.X >= size.X ||
          currentLocation.Y >= size.Y)
        return false;
      if(!IsTypeOf(static_cast<MazeTileType>(tileMap->GetTileTag(currentLocation)), tiles[x][y]) ||
          IsTypeOf(static_cast<MazeTileType>(tileMap->GetTileTag(currentLocation)), MazeTileType::OBSTICLE) ||
          IsTypeOf(static_cast<MazeTileType>(tileMap->GetTileTag(currentLocation)), MazeTileType::GOAL) ||
          IsTypeOf(static_cast<MazeTileType>(tileMap->GetTileTag(currentLocation)), MazeTileType::START))
        return false;
    }
  }
  return true;
}

struct FitResult
{
  bool isFitable;
  Direction4 dir;
  TrapSpaceTiles usedTiles;
};

FitResult IsFitable(const ATileMap* tileMap, const FIntPoint& start,
                    TrapSpaceTiles tiles) {
  for (int32 dir = 0; dir < 4; dir++) {
    if (IsFitableInDirection(tileMap, start, tiles)) {
      return {true, static_cast<Direction4>(dir), tiles};
    }
    RotateLeft(tiles);
  }
  return {false, {}, {}};
}

FitResult IsFitable(const ATileMap* tileMap, const FIntPoint& start,
                    TrapSpase trapSpase) {
  return IsFitable(tileMap, start, GetTrapSpaceMap()[trapSpase]);
}

void FillMaze(ATileMap* tileMap, const FIntPoint& start,const TrapSpaceTiles& tiles)
{
  const auto size = tileMap->Size();
  for (int32 x = 0; x < 3; x++) {
    for (int32 y = 0; y < 3; y++) {
      FIntPoint currentLocation = start + FIntPoint{x, y};
      if (currentLocation.X >= size.X || currentLocation.Y >= size.Y)
        return;
      if (IsTypeOf(tiles[x][y], MazeTileType::PATH)) {
        tileMap->SetTileTag(currentLocation, static_cast<int32>(MazeTileType::OBSTICLE));
      }
		}
	}
}

AActivable* TryPlaceTrap(ATileMap* tileMap,  const FTrap& trap, const FIntPoint& start)
{
  const FitResult fit = IsFitable(tileMap, start, trap.requiredSpace);
  if (fit.isFitable) {
    const FIntPoint spawnLocation = start + FIntPoint{1, 1};
    FillMaze(tileMap, start, fit.usedTiles);
    return Cast<AActivable>(tileMap->SpawnActorAt(
        UUtilsLibrary::GetRandomType(trap.trapTypes), spawnLocation, fit.dir));
  }
	return nullptr;
}

void ATrapGenerator::Destruct()
{
}

void ATrapGenerator::Construct()
{
  if (!tileMap) return;
  const auto size = tileMap->Size();
  for (int32 x = 0; x < size.X; x++) {
    for (int32 y = 0; y < size.Y; y++) {
      for (const auto& trap : trapTypes) {
      	TryPlaceTrap(tileMap, trap, {x, y});
      }
    }
  }
}

