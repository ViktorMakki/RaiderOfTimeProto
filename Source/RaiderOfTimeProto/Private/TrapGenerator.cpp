// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapGenerator.h"

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

bool IsFitableInDirection(const ABP_Maze* maze, const FIntPoint& start,
                          const TrapSpaceTiles& tiles)
{
  for (int32 x = 0; x < 3; x++) {
    for (int32 y = 0; y < 3; y++) {
      FIntPoint currentLocation = start + FIntPoint{x, y};
      if (currentLocation.X >= maze->GetTiles().Num() ||
          currentLocation.Y >= maze->GetTiles().Num())
        return false;
      if(!IsTypeOf(maze->GetTileType(currentLocation), tiles[x][y]) || currentLocation == maze->start)
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

FitResult IsFitable(const ABP_Maze* maze, const FIntPoint& start,
                    TrapSpaceTiles tiles) {
  for (int32 dir = 0; dir < 4; dir++) {
    if (IsFitableInDirection(maze, start, tiles)) {
      return {true, static_cast<Direction4>(dir), tiles};
    }
    RotateLeft(tiles);
  }
  return {false, {}, {}};
}

FitResult IsFitable(const ABP_Maze* maze, const FIntPoint& start,
                    TrapSpase trapSpase) {
  return IsFitable(maze, start, GetTrapSpaceMap()[trapSpase]);
}

void FillMaze(ABP_Maze* maze, const FIntPoint& start,const TrapSpaceTiles& tiles)
{
	for (int32 x = 0; x < 3; x++) {
		for (int32 y = 0; y < 3; y++) {
			FIntPoint currentLocation = start + FIntPoint{x, y};
			if (currentLocation.X >= maze->GetTiles().Num() ||
					currentLocation.Y >= maze->GetTiles().Num())
						return ;
      if (IsTypeOf(tiles[x][y], MazeTileType::PATH)) {
        maze->SetTileType(currentLocation, MazeTileType::OBSTICLE);
      }
		}
	}
}

ABP_Obsticle* TryPlaceTrap(ABP_Maze* maze,  const FMazeTrap& trap, const FIntPoint& start)
{
  const FitResult fit = IsFitable(maze, start, trap.requiredSpace);
  if (fit.isFitable) {
    const FIntPoint spawnLocation = start + FIntPoint{1, 1};
    FillMaze(maze, start, fit.usedTiles);
    return  Cast<ABP_Obsticle>(maze->SpawnActorAt(trap.trapType, spawnLocation, fit.dir));
  }
	return nullptr;
}

TArray<ABP_Obsticle*> UTrapGenerator::GenerateTraps(ABP_Maze* maze, const TArray<FMazeTrap>& traps)
{
  TArray<ABP_Obsticle*> result;

  for (int32 x = 0; x < maze->GetTiles().Num(); x ++) {
    for (int32 y = 0; y < maze->GetTiles()[x].tiles.Num(); y ++) {
      for (const auto& trap : traps) {
        ABP_Obsticle* newTrap = TryPlaceTrap(maze, trap, {x, y});
        if (newTrap) {
          result.Add(newTrap);
        }
      }
    }
  }
  return result;
}
