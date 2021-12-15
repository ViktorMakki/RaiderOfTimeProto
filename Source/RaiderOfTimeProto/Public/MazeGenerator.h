// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MazeTypes.h"
#include "MazeGenerator.generated.h"


USTRUCT(BlueprintType)
struct FMazeGeneratorConstructData {
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

USTRUCT(BlueprintType)
struct FMazeGenerationResult {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  TArray<FTileArray> tiles;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  TArray<FChamber> chambers;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  TArray<FDoor> doors;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  TArray<FSiblingDoors> siblingDoors;
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
