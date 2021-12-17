// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathSearcher.h"
#include "MazeTypes.h"

#include "MazePath.generated.h"

/**
 * 
 */
UCLASS()
class RAIDEROFTIMEPROTO_API UMazePath : public UObject
{

  GENERATED_BODY()
public:
  UFUNCTION(BlueprintCallable)
  TArray<FPathSegment> GetPathToGoal() const;

  UFUNCTION(BlueprintCallable)
  TArray<FPathSegment> GetPathEndings() const;

  UFUNCTION(BlueprintCallable)
  FPathSegment GetRoot() const;

	UFUNCTION(BlueprintCallable)
  FPathSegment GetFarestLeaf() const;

  void SetPath(TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path);

  TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> GetPath() const;

  static TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>>
	GetSegmentsInDistance(const TArray<FTileArray>& maze,
												const FIntPoint& start,
												Direction4 startDirection,
												int32 distance);

 private:
  void Init(const TArray<FTileArray>& maze, const FIntPoint& goal);
  void Init(const TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path);

	TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path_;
  TSharedPtr<Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>> start_;

public:
	template <class... Types>
  static UMazePath* Create(const Types&... args);
};

template <class ... Types>
UMazePath* UMazePath::Create(const Types&... args)
{
  auto newMaze = NewObject<UMazePath>();
  newMaze->Init(args...);
  return newMaze;
}
