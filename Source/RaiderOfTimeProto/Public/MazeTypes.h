// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeTypes.generated.h"

UENUM(BlueprintType,
      meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class MazeTileType : uint8 {
  EMPTY = 0,
  PATH = 1 << 0,
  DOOR = PATH | 1 << 1,
  GOAL = PATH | 1 << 2,
  START = PATH | 1 << 3,
  PATHTOGOAL = PATH | 1 << 4,
  WALL = 1 << 5,

};
ENUM_CLASS_FLAGS(MazeTileType);

inline bool IsTypeOf(MazeTileType type, MazeTileType parent) {
  return (type & parent) == parent;
}

UENUM(BlueprintType)
enum class Direction4 : uint8 {
  DOWN = 0 UMETA(DisplayName = "DOWN"),
  LEFT = 1 UMETA(DisplayName = "LEFT"),
  UP = 2 UMETA(DisplayName = "UP"),
  RIGHT = 3 UMETA(DisplayName = "RIGHT")
};

static Direction4 SwapDirection(Direction4 direction)
{
  return static_cast<Direction4>((static_cast<int8>(direction) + 2) % 4);
}

USTRUCT(BlueprintType)
struct FTile {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  MazeTileType tile;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  int32 recursionLevel;
};

USTRUCT(BlueprintType)
struct FTileArray {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  TArray<FTile> tiles;
};

USTRUCT(BlueprintType)
struct FChamber {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FIntPoint leftBottom;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FIntPoint rightTop;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  int32 recursionLevel;
};

USTRUCT(BlueprintType)
struct FDoor {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FIntPoint location;

  /** Whether the path_ orientation through is horizontal */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  bool isHorizontal;

  /** Which chamber is splitted by this */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FChamber chamber;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  int32 recursionLevel;
};

/** Doors that are on the same wall, splitting the same chamber*/
USTRUCT(BlueprintType)
struct FSiblingDoors {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FDoor door1;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FDoor door2;
};

USTRUCT(BlueprintType)
struct FActorArray {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  TArray<AActor*> actors;
};

USTRUCT(BlueprintType)
struct FActor2DArray {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  TArray<FActorArray> actors;
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

