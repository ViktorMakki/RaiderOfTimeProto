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

UMazePath::UMazePath() {}

UMazePath::UMazePath(const TArray<FTileArray>& maze, const FIntPoint& goal)
{
	Graph::PathSearcherInput<FIntPoint, Direction4> input;
	input.startPoint =
		TPair<FIntPoint, TArray<Direction4>>{goal,
			GetAvailableDirections(goal, maze)},
	input.GetNextPointCallback = GetNextLocation;
	input.GetAvailableEdgesCallback = [&maze](const FIntPoint& location) {
		return GetAvailableDirections(location, maze);
	};
	path_ = Graph::PathSearcher::DFS(input);
  start_ = path_->GetDeepestLeaf();
  path_->ForEachToRoot(
      [](Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>& point) {
        point.data.isToGoal = true;
        return false;},
      *start_);
}

UMazePath::UMazePath(const TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path)
	:path_(path), start_(path->GetDeepestLeaf()){}

TArray<FPathSegment> UMazePath::GetPathToGoal() const
{
  TArray<FPathSegment> result;
  path_->ForEachToRoot(
      [&result](const Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>& point) {
        const Direction4 goalDirection = point.GetEdgeToParent();
        TArray<Direction4> availableDirections = point.GetEdgesToChildren();
        availableDirections.Add(goalDirection);
        result.Add({point.data.data, goalDirection, availableDirections});
      	return false;
      },*start_);
  return result;
}

FPathSegment UMazePath::GetRoot() const
{
  if (!path_) return {};
  const auto root = path_->GetRoot();
  const TArray<Direction4> availableDirections = root->GetEdgesToChildren();
  // for goal direction the first available direction is set
  return {root->data.data, availableDirections[0], availableDirections};
}

FPathSegment UMazePath::GetFarestLeaf() const
{
  if (!path_) return {};
  const auto leaf = path_->GetDeepestLeaf();
  const Direction4 availableDirections = leaf->GetEdgeToParent();
  return {leaf->data.data, availableDirections, {availableDirections}};
}

void UMazePath::SetPath(TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path)
{
  this->path_ = path;
  start_ = path->GetDeepestLeaf();
}

TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>>
UMazePath::GetSegmentsInDistance(
    const TArray<FTileArray>& maze, const FIntPoint& start,
    Direction4 startDirection, int32 distance)
{
	Graph::PathSearcherInput<FIntPoint, Direction4> input;
  input.startPoint = TPair<FIntPoint, TArray<Direction4>>{start, TArray<Direction4>{startDirection}};
  input.GetNextPointCallback = GetNextLocation;
  input.GetAvailableEdgesCallback = [&maze](const FIntPoint& location) {
    return GetAvailableDirections(location, maze);
  };
  input.maxDepth = distance;

	return Graph::PathSearcher::DFS(input);
}

