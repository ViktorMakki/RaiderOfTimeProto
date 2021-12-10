// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.h"

#include "BP_Maze.generated.h"

USTRUCT(BlueprintType)
struct FActorArray 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<AActor*>	actors;
};

USTRUCT(BlueprintType)
struct FActor2DArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	TArray<FActorArray>	actors;
};

UCLASS()
class RAIDEROFTIMEPROTO_API ABP_Maze : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Maze();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FActor2DArray> actors = {};
	FMazeGenerationResult mazeData;
	FIntPoint start;
	FIntPoint end;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	UClass* pathClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	UClass* wallsClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	UClass* debugClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	float tileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	FMazeGeneratorConstructData mazeConstructionData;

	UFUNCTION(BlueprintCallable, category = "Maze")
	void GenerateMaze();

	UFUNCTION(BlueprintCallable, category = "Maze")
	TArray<AActor*>& GetActorsAt(const FIntPoint& location);

	UFUNCTION(BlueprintCallable, category = "Maze")
	void DebugGoalPath();
};
