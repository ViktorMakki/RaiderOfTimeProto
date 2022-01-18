// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TileMap.generated.h"

UENUM(BlueprintType)
enum class Direction4 : uint8 {
  DOWN = 0 UMETA(DisplayName = "DOWN"),
  LEFT = 1 UMETA(DisplayName = "LEFT"),
  UP = 2 UMETA(DisplayName = "UP"),
  RIGHT = 3 UMETA(DisplayName = "RIGHT")
};


USTRUCT(BlueprintType)
struct FTile {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMap")
  TArray<AActor*> actors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMap")
  FIntPoint location;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMap")
  int32 tag;
};

USTRUCT(BlueprintType)
struct FTileArray {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utils")
  TArray<FTile> tiles;
};

UCLASS()
class RAIDEROFTIMEPROTO_API ATileMap : public AActor
{
	GENERATED_BODY()
	
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  float tileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
  FIntPoint tileCount;

	// Sets default values for this actor's properties
	ATileMap();

	UFUNCTION(BlueprintCallable, CallInEditor, category = "TileMap")
	void Create();

	UFUNCTION(BlueprintCallable, category = "TileMap")
	const FTile& GetConstTile(const FIntPoint& location) const;
	
	UFUNCTION(BlueprintCallable, category = "TileMap")
	FTile& GetTile(const FIntPoint& location);

	UFUNCTION(BlueprintCallable, category = "TileMap")
	int32 GetTileTag(const FIntPoint& location) const;

	UFUNCTION(BlueprintCallable, category = "TileMap")
	void SetTileTag(const FIntPoint& location, int32 tag);

	UFUNCTION(BlueprintCallable, category = "TileMap")
	const TArray<AActor*>& GetConstActorsAt(const FIntPoint& location) const;

	UFUNCTION(BlueprintCallable, category = "TileMap")
	TArray<AActor*>& GetActorsAt(const FIntPoint& location);

	UFUNCTION(BlueprintCallable, category = "TileMap")
	AActor* SpawnActorAt(UClass* type, const FIntPoint& location, Direction4 direction = Direction4::UP);

	UFUNCTION(BlueprintCallable, category = "TileMap")
	void DestroyActorsAt(const FIntPoint& location);

	UFUNCTION(BlueprintCallable, category = "TileMap")
	void ClearActors();

	UFUNCTION(BlueprintCallable, category = "TileMap")
	void Clear();

	UFUNCTION(BlueprintCallable, category = "TileMap")
	FIntPoint GetLocation(const AActor* actor) const;

	UFUNCTION(BlueprintCallable, category = "TileMap")
	FIntPoint Size() const;

	UFUNCTION(BlueprintCallable, category = "TileMap")
	void SetSize(FIntPoint size);

	UFUNCTION(BlueprintCallable, category = "TileMap")
	FTile GetFirstTileByTag(int32 tag) const;

private:
	TArray<FTileArray> tiles;
};
