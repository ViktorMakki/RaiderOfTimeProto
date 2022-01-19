// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePath.h"
#include "UtilsLibrary.h"

TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> Search(
    const Graph::PathSearcherInput<FIntPoint, Direction4>& input,
    SearchAlgorithm algo)
{
	switch (algo) {
    case SearchAlgorithm::BFS:
      return Graph::PathSearcher::BFS(input);
    case SearchAlgorithm::DFS:
      return Graph::PathSearcher::DFS(input);
	default: ;
	}
	return {};
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

TArray<FPathSegment> UMazePath::GetPathToGoal() const
{
  auto leafs = path_->GetLeafs();
  if (leafs.IsEmpty()) return {};
  auto goal = Find<TSharedPtr<Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>>>(
      leafs,
      [](const TSharedPtr<
          Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>>& item) {
        return item->data.isToGoal;
      });
  if (!goal) return {};
  TArray<FPathSegment> result;
  path_->ForEachToRoot(
      [&result](const Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>& point) {
        const Direction4 goalDirection = static_cast<Direction4>((static_cast<int32>(point.GetEdgeToParent()) + 2) % 4);
        TArray<Direction4> availableDirections = point.GetEdgesToChildren();
        availableDirections.Add(goalDirection);
        result.Add({point.data.data, goalDirection, availableDirections});
      	return false;
      },*goal);
  Reverse(result);
  return result;
}

TArray<FPathSegment> UMazePath::GetPathEndings() const
{
  TArray<FPathSegment> result;
	for (const auto point : path_->GetLeafs()) {
    const Direction4 goalDirection = point->GetEdgeToParent();
    result.Add({point->data.data, goalDirection, {goalDirection}});
	}
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

UMazePath* StepOneToGoal(const UMazePath* from)
{
  auto root = from->GetPath()->GetRoot();
  for (auto point : root->GetChildren()) {
    if (point->data.isToGoal)
      return UMazePath::Create(
          TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>>{
              new Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>(point)});
  }
  return nullptr;
}

UMazePath* UMazePath::StepToGoal(int32 stepCount) const
{
  UMazePath* result = nullptr;
  for (int step = 0; step < stepCount; step++) {
    result = StepOneToGoal(this);
    if (!result) return nullptr;
  }
  return result;
}

void UMazePath::SetPath(TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path)
{
  path_ = path;
}

TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> UMazePath::GetPath() const
{
  return path_;
}

TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>>
UMazePath::GetSegmentsInDistance(const ATileMap* maze, const FIntPoint& start,
                                 Direction4 startDirection, int32 distance)
{
	Graph::PathSearcherInput<FIntPoint, Direction4> input;
  input.startPoint = TPair<FIntPoint, TArray<Direction4>>{start, TArray<Direction4>{startDirection}};
  input.GetNextPointCallback = GetNextLocation;
  input.GetAvailableEdgesCallback = [&maze](const FIntPoint& location) {
    return UUtilsLibrary::GetAvailableDirectionsInMaze(location, maze);
  };
  input.maxDepth = distance;

	return Graph::PathSearcher::BFS(input);
}

void UMazePath::Init(const ATileMap* maze, const FIntPoint& start,
                     SearchAlgorithm algo)
{
  Graph::PathSearcherInput<FIntPoint, Direction4> input;
  input.startPoint =
      TPair<FIntPoint, TArray<Direction4>>{start, UUtilsLibrary::GetAvailableDirectionsInMaze(start, maze)},
  input.GetNextPointCallback = GetNextLocation;
  input.GetAvailableEdgesCallback = [&maze](const FIntPoint& location) {
    return UUtilsLibrary::GetAvailableDirectionsInMaze(location, maze);
  };
  path_ = Search(input, algo);
  auto goal = path_->GetDeepestLeaf();
  path_->ForEachToRoot(
      [](Graph::TreePoint<Graph::PathPoint<FIntPoint>, Direction4>& point) {
        point.data.isToGoal = true;
        return false;
      },
      *goal);
}

void UMazePath::Init(const ATileMap* maze, 
                     const FIntPoint& start,
                     const FIntPoint& goal, 
                     SearchAlgorithm algo)
{
  Graph::PathSearcherInput<FIntPoint, Direction4> input;
  input.startPoint =
      TPair<FIntPoint, TArray<Direction4>>{start,
                                           UUtilsLibrary::GetAvailableDirectionsInMaze(start, maze)},
  input.GetNextPointCallback = GetNextLocation;
  input.GetAvailableEdgesCallback = [&maze](const FIntPoint& location) {
    return UUtilsLibrary::GetAvailableDirectionsInMaze(location, maze);
  };

  input.IsGoalCallback = [&goal](const FIntPoint& location){
    return location == goal;
  };

  path_ = Search(input, algo);
}

void UMazePath::Init(const TSharedPtr<Graph::Tree<Graph::PathPoint<FIntPoint>, Direction4>> path)
{
  SetPath(path);
}

