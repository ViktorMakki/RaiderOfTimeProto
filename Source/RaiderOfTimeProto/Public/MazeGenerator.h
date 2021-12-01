// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MazeGenerator.generated.h"

UENUM(BlueprintType)
enum class MazePathDirection : uint8 
{
	DOWN = 0 UMETA(DisplayName = "DOWN"),
	LEFT = 1  UMETA(DisplayName = "LEFT"),
	UP = 2     UMETA(DisplayName = "UP"),
	RIGHT = 3 UMETA(DisplayName = "RIGHT")
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class MazeTileType : uint8
{
	WALL = 0,
	PATH = 1 << 0,
	DOOR = PATH | 1 << 1,
	ONE_WAY_DOOR =  DOOR | 1 << 2,
	TWO_WAY_DOOR =  DOOR | 1 << 3,
	GOAL =	PATH | 1 << 4,
	START =	PATH | 1 << 5
};
ENUM_CLASS_FLAGS(MazeTileType);

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	MazeTileType tile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 recursionLevel;
};


// Need to know chamber hierarchy with levels
// Need to know Doors with levels
// 2-way doors
// Goal tiles
// start tile
USTRUCT(BlueprintType)
struct FTileArray 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	TArray<FTile> tiles;
};

USTRUCT(BlueprintType)
struct FChamber
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	FIntPoint leftBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	FIntPoint rightTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 recursionLevel;
};

USTRUCT(BlueprintType)
struct FMazeGenerationResult 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	TArray<FTileArray> tiles;
};

USTRUCT(BlueprintType)
struct FMazeGeneratorData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 width = 21;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 height = 21;
};

UCLASS(Blueprintable)
class RAIDEROFTIMEPROTO_API UMazeGenerator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, category = "MazeGenerator")
	static TArray<FTileArray> GenerateMaze(const FMazeGeneratorData& data);
};
