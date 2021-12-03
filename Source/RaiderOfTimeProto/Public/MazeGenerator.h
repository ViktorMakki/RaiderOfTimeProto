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
	GOAL =	PATH | 1 << 2,
	START =	PATH | 1 << 3
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
struct FDoor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	FIntPoint location;

	/** Whether the path orientation through is horizontal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	bool isHorizontal;

	/** Which chamber is splitted by this */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	FChamber chamber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 recursionLevel;
};

/** Doors that are on the same wall, splitting the same chamber*/
USTRUCT(BlueprintType)
struct FSimblingDoors 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	FDoor door1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	FDoor door2;
};

USTRUCT(BlueprintType)
struct FMazeGenerationResult 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	TArray<FTileArray> tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	TArray<FChamber> chambers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	TArray<FDoor> doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	TArray<FSimblingDoors> siblingDoors;

};

USTRUCT(BlueprintType)
struct FMazeGeneratorConstructData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 mazeWidth = 21;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 mazeHeight = 21;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 goalWidth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 goalHeight = 3;

	/**From what chamber size is enabled to make circle*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 CircleSizeStart = 0;

	/**From what chamber size is enabled to make circle*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	int32 CircleSizeEnd = 0;

};

UCLASS(Blueprintable)
class RAIDEROFTIMEPROTO_API UMazeGenerator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, category = "MazeGenerator")
	static FMazeGenerationResult GenerateMaze(const FMazeGeneratorConstructData& data);

	UFUNCTION(BlueprintCallable, category = "MazeTileMask")
		static bool IsTypeOf(MazeTileType child, MazeTileType parent);
};
