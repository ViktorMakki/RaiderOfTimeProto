// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MazeGenerator.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	MazeTileType tile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 recursionLevel;
};

USTRUCT(BlueprintType)
struct FTileArray 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FTile> tiles;
};

USTRUCT(BlueprintType)
struct FChamber
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FIntPoint leftBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FIntPoint rightTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 recursionLevel;
};

USTRUCT(BlueprintType)
struct FDoor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FIntPoint location;

	/** Whether the path orientation through is horizontal */
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
struct FSimblingDoors 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FDoor door1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FDoor door2;
};

USTRUCT(BlueprintType)
struct FMazeGenerationResult 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FTileArray> tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FChamber> chambers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FDoor> doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FSimblingDoors> siblingDoors;

};

USTRUCT(BlueprintType)
struct FMazeGeneratorConstructData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 mazeWidth = 21;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 mazeHeight = 21;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 goalWidth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 goalHeight = 3;

	/**From what chamber size is enabled to make circle*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 CircleSizeStart = 0;

	/**From what chamber size is enabled to make circle*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 CircleSizeEnd = 0;

};

UCLASS(Blueprintable)
class RAIDEROFTIMEPROTO_API UMazeGenerator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, category = "Maze")
	static FMazeGenerationResult GenerateMaze(const FMazeGeneratorConstructData& data);

	UFUNCTION(BlueprintCallable, category = "Maze")
		static bool IsTypeOf(MazeTileType child, MazeTileType parent);
};
