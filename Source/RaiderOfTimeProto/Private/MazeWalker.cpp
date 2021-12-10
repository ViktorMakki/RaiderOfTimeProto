// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeWalker.h"

#include "PathSearcher.h"

using namespace PathSearching;

template<class Type>
std::vector<Type> Cast(const TArray<Type>& array) 
{
	std::vector<Type> result;
	for (const auto& item : array) {
		result.push_back(item);
	}
	return result;
}

template<class Type>
TArray<Type> Cast(const std::vector<Type>& vector) {
  TArray<Type> result;
	for (const auto& item : vector) {
		result.Add(item);
	}
	return result;
}

TArray<FPathSegment> Cast(const std::vector<PathPoint<FIntPoint, MazePathDirection>> points) 
{
	TArray<FPathSegment> result;
	for (const auto& item : points) {
		result.Add({ item.point.data, Cast(item.point.edges), item.distance});
	}
	return result;
}

std::vector<MazePathDirection> GetAvailableDirections(const FIntPoint& point, const TArray<FTileArray>& maze) 
{
	std::vector<MazePathDirection> result;
	if (UMazeGenerator::IsTypeOf(maze[point.X].tiles[point.Y + 1].tile, MazeTileType::PATH))
		result.push_back(MazePathDirection::UP);
	if (UMazeGenerator::IsTypeOf(maze[point.X].tiles[point.Y - 1].tile, MazeTileType::PATH))
		result.push_back(MazePathDirection::DOWN);
	if (UMazeGenerator::IsTypeOf(maze[point.X + 1].tiles[point.Y].tile, MazeTileType::PATH))
		result.push_back(MazePathDirection::RIGHT);
	if (UMazeGenerator::IsTypeOf(maze[point.X - 1].tiles[point.Y].tile, MazeTileType::PATH))
		result.push_back(MazePathDirection::LEFT);
	return result;
}

FIntPoint GetNextLocation(const FIntPoint& from, MazePathDirection direction)
{
  switch (direction) {
    case MazePathDirection::UP:
      return from + FIntPoint{0, 1};
    case MazePathDirection::DOWN:
      return from + FIntPoint{0, -1};
    case MazePathDirection::RIGHT:
      return from + FIntPoint{1, 0};
    case MazePathDirection::LEFT:
      return from + FIntPoint{-1, 0};
    default:
      return {};
  }
}

FMazeWalkResult UMazeWalker::GetPathToGoal(const FMazeWalkToGoalInput& inputData)
{
	FMazeWalkResult result;
	PathSearcherInput<FIntPoint, MazePathDirection> dfsInput;
	dfsInput.startPoint = { inputData.start };
	dfsInput.startPoint.edges = { GetAvailableDirections(inputData.start, inputData.maze) };
	dfsInput.GetNextPointCallback = [&inputData](const FIntPoint& location, const MazePathDirection& direction)
	{
		Point<FIntPoint, MazePathDirection> result;
		result.data = GetNextLocation(location, direction);
		result.edges = GetAvailableDirections(result.data, inputData.maze);
		return result;
	};
	dfsInput.IsGoalCallback = [&inputData](const FIntPoint& location) { return location == inputData.goal; };
	const auto dfsResult = PathSearcher::DFS(dfsInput);
	result.path = Cast(dfsResult.pathToGoal);
	return result;
}

FMazeWalkResult UMazeWalker::GetPathToDepth(const FMazeWalkToDepthInput& inputData)
{
	FMazeWalkResult result;
	PathSearcherInput<FIntPoint, MazePathDirection> dfsInput;
	dfsInput.startPoint = { inputData.startSegment.location };
	dfsInput.startPoint.edges = { Cast(inputData.startSegment.directions) };
	dfsInput.maxDepth = inputData.maxDepth;
	dfsInput.GetNextPointCallback = [&inputData](const FIntPoint& location, const MazePathDirection& direction)
	{
		Point<FIntPoint, MazePathDirection> result;
		result.data = GetNextLocation(location, direction);
		result.edges = GetAvailableDirections(result.data, inputData.maze);
		return result;
	};
	dfsInput.IsGoalCallback = [](const FIntPoint& /*location*/) { return false; };
	const auto dfsResult = PathSearcher::DFS(dfsInput);
	result.path = Cast(dfsResult.walkedPoints);
	return result;
}

FIntPoint FindFarest(const TArray<FPathSegment>& segments)
{
  int32 distance = 0;
  FIntPoint farestTemp;
	for(const auto& segment : segments) {
    if (distance < segment.distance) {
    	distance = segment.distance;
      farestTemp = segment.location;
    }
  }
	return farestTemp;
}

FIntPoint UMazeWalker::GetFarestLocation(const TArray<FTileArray>& maze, const FIntPoint& start)
{
  FMazeWalkResult result;
  PathSearcherInput<FIntPoint, MazePathDirection> dfsInput;
  dfsInput.startPoint = {start};
  dfsInput.startPoint.edges = GetAvailableDirections(start, maze);
  dfsInput.GetNextPointCallback = [&maze](const FIntPoint& location, const MazePathDirection& direction) {
    Point<FIntPoint, MazePathDirection> result;
    result.data = GetNextLocation(location, direction);
    result.edges = GetAvailableDirections(result.data, maze);
    return result;
  };

  dfsInput.IsGoalCallback = [](const FIntPoint& /*location*/) { return false; };
  const auto dfsResult = PathSearcher::DFS(dfsInput);
  result.path = Cast(dfsResult.walkedPoints);
  return FindFarest(result.path);
}
