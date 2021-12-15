// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePath.h"
#include "MazeGenerator.h"

TArray<Direction4> GetAvailableDirections(
    const FIntPoint& point, const TArray<FTileArray>& maze) {
  TArray<Direction4> result;
  if (UMazeGenerator::IsTypeOf(maze[point.X].tiles[point.Y + 1].tile,
                               MazeTileType::PATH))
    result.Add(Direction4::UP);
  if (UMazeGenerator::IsTypeOf(maze[point.X].tiles[point.Y - 1].tile,
                               MazeTileType::PATH))
    result.Add(Direction4::DOWN);
  if (UMazeGenerator::IsTypeOf(maze[point.X + 1].tiles[point.Y].tile,
                               MazeTileType::PATH))
    result.Add(Direction4::RIGHT);
  if (UMazeGenerator::IsTypeOf(maze[point.X - 1].tiles[point.Y].tile,
                               MazeTileType::PATH))
    result.Add(Direction4::LEFT);
  return result;
}

FIntPoint GetNextLocation(const FIntPoint& from, Direction4 direction) {
  switch (direction) {
    case Direction4::UP:
      return from + FIntPoint{0, 1};
    case Direction4::DOWN:
      return from + FIntPoint{0, -1};
    case Direction4::RIGHT:
      return from + FIntPoint{1, 0};
    case Direction4::LEFT:
      return from + FIntPoint{-1, 0};
    default:
      return {};
  }
}

MazePath::MazePath(const TArray<FTileArray>& maze, const FIntPoint& goal)
{
	Graph::PathSearcherInput<FIntPoint, Direction4> input;
	input.startPoint =
		TPair<FIntPoint, TArray<Direction4>>{goal,
			GetAvailableDirections(goal, maze)},
	input.GetNextPointCallback = GetNextLocation;
	input.GetAvailableEdgesCallback = [&maze](const FIntPoint& location) {
		return GetAvailableDirections(location, maze);
	};
	path = Graph::PathSearcher::DFS(input);
  start = path->GetDeepestLeaf();
  path->ForEachToRoot(
      [](Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>& point) {
        point.data.isToGoal = true;
        return false;},
      *start);
}

TArray<FPathSegment> MazePath::GetPathToGoal() const
{
  TArray<FPathSegment> result;
  path->ForEachToRoot(
      [&result](const Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>& point) {
        const Direction4 goalDirection = point.GetEdgeToParent();
        TArray<Direction4> availableDirections = point.GetEdgesToChildren();
        availableDirections.Add(goalDirection);
        result.Add({point.data.data, goalDirection, availableDirections});
      	return false;
      },*start);
  return result;
}
