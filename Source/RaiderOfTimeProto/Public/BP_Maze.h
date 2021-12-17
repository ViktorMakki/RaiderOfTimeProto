// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.h"
#include "MazeTypes.h"
#include "MazePath.h"

#include "BP_Maze.generated.h"

UCLASS()
class RAIDEROFTIMEPROTO_API ABP_Maze : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Maze();

protected:
	TArray<FActor2DArray> actors = {};
	FMazeGenerationResult mazeData;
public:
  UPROPERTY(BlueprintReadOnly, Category = "Maze")
  FIntPoint end;

	UPROPERTY(BlueprintReadOnly, Category = "Maze")
  FIntPoint start;

	UPROPERTY(BlueprintReadOnly, Category = "Maze")
  UMazePath* path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	UClass* pathClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	UClass* wallsClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	UClass* startClass;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	 UClass* goalClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	UClass* debugClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	float tileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FMazeGeneratorConstructData mazeConstructionData;

	UFUNCTION(BlueprintCallable, category = "Maze")
	const TArray<FTileArray>& GetTiles() const;

	UFUNCTION(BlueprintCallable, category = "Maze")
	MazeTileType GetTileType(const FIntPoint& location) const;

	UFUNCTION(BlueprintCallable, category = "Maze")
	ABP_Maze* GenerateMaze();

	UFUNCTION(BlueprintCallable, category = "Maze")
	TArray<AActor*>& GetActorsAt(const FIntPoint& location);

	UFUNCTION(BlueprintCallable, category = "Maze")
	AActor* SpawnActorAt(UClass* type,const FIntPoint& location, Direction4 direction);

	UFUNCTION(BlueprintCallable, category = "Maze")
	void DebugGoalPath();
};
