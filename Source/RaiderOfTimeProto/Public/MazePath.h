// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathSearcher.h"
#include "MazeTypes.h"

/**
 * 
 */
class RAIDEROFTIMEPROTO_API MazePath
{
public:
  MazePath(const TArray<FTileArray>& maze, const FIntPoint& goal);

  TArray<FPathSegment> GetPathToGoal() const;
 private:
	TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path;
  TSharedPtr<Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>> start;
};
