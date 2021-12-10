// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MazeGenerator.h"

#include "MazeWalker.generated.h"

UENUM(BlueprintType)
enum class MazePathDirection : uint8
{
	DOWN = 0 UMETA(DisplayName = "DOWN"),
	LEFT = 1  UMETA(DisplayName = "LEFT"),
	UP = 2     UMETA(DisplayName = "UP"),
	RIGHT = 3 UMETA(DisplayName = "RIGHT")
};

USTRUCT(BlueprintType)
struct FPathSegment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FIntPoint location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<MazePathDirection> directions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 distance;
};

USTRUCT(BlueprintType)
struct FMazeWalkResult 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FPathSegment> path;
};

USTRUCT(BlueprintType)
struct FMazeWalkToDepthInput
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int32 maxDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FPathSegment startSegment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FTileArray> maze;
};

USTRUCT(BlueprintType)
struct FMazeWalkToGoalInput
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FIntPoint start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FIntPoint goal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FTileArray> maze;
};

/**
 * 
 */
UCLASS()
class RAIDEROFTIMEPROTO_API UMazeWalker : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, category = "Maze")
	static FMazeWalkResult GetPathToGoal(const FMazeWalkToGoalInput& inputData);

	UFUNCTION(BlueprintCallable, category = "Maze")
	static FMazeWalkResult GetPathToDepth(const FMazeWalkToDepthInput& inputData);

	UFUNCTION(BlueprintCallable, category = "Maze")
	static FIntPoint GetFarestLocation(const TArray<FTileArray>& maze, const FIntPoint& start);
};
