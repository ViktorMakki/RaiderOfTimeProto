// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileMap.h"
#include "MazeTypes.generated.h"

UENUM(BlueprintType,
      meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class MazeTileType : uint8 {
  EMPTY = 0,
  PATH = 1 << 0,
  START = PATH | 1 << 1,
  GOAL = PATH | 1 << 2,
  OBSTICLE = PATH | 1 << 3,
  GATE = OBSTICLE | 1 << 4,
  GOALGATE = OBSTICLE | 1 << 5,
  WALL = 1 << 6
};
ENUM_CLASS_FLAGS(MazeTileType);

inline bool IsTypeOf(MazeTileType type, MazeTileType parent) {
  return (type & parent) == parent;
}


static Direction4 SwapDirection(Direction4 direction)
{
  return static_cast<Direction4>((static_cast<int8>(direction) + 2) % 4);
}

USTRUCT(BlueprintType)
struct FSymbol{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  int32 id;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FColor color;

  bool operator==(const FSymbol& other) const{
  	return id == other.id;
  }
};

USTRUCT(BlueprintType)
struct FMazeTile {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  MazeTileType tile;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  int32 recursionLevel;
};

USTRUCT(BlueprintType)
struct FPathSegment {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FIntPoint location;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  Direction4 directionToGoal;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  TArray<Direction4> directionsAvailable;
};