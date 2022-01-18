// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathSearcher.h"
#include "MazeTypes.h"

#include "MazePath.generated.h"

enum class SearchAlgorithm
{
	BFS,
	DFS
};

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

	UFUNCTION(BlueprintCallable)
  UMazePath* StepToGoal(int32 stepCount) const;

  void SetPath(TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path);

  TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> GetPath() const;

  static TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>>
  GetSegmentsInDistance(const ATileMap* maze,
												const FIntPoint& start,
												Direction4 startDirection,
												int32 distance);

 private:
  void Init(const ATileMap* maze, const FIntPoint& start,
            SearchAlgorithm algo = SearchAlgorithm::BFS);
  void Init(const ATileMap* maze, const FIntPoint& start, const FIntPoint& goal,
            SearchAlgorithm algo = SearchAlgorithm::BFS);

  void Init(const TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path);

	TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path_;

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
