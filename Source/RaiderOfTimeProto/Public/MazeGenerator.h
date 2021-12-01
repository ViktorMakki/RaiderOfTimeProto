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

UENUM(BlueprintType)
enum class MazeTileType : uint8
{
	PATH = 0 UMETA(DisplayName = "PATH"),
	WALL = 1  UMETA(DisplayName = "WALL")
};

USTRUCT(BlueprintType)
struct FTileArray 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MazeGenerator")
	TArray<MazeTileType> tiles;
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
