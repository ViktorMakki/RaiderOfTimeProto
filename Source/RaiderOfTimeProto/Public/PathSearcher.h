// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include <Tree.h>

namespace Graph {
template <class DataType>
struct PathPoint {
  DataType data;
  bool isToGoal = false;
};

template<class DataType, class EdgeType>
struct PathSearchResult 
{
	//path starts with goal and ends with the start point
	//Contains points with 1 edge
  Tree<PathPoint<DataType>, EdgeType> pathTree;
};

template<class DataType, class EdgeType>
struct PathSearcherInput 
{
	// starting point with available edges
  TPair<DataType, TArray<EdgeType>> startPoint;

	//How deep should the algorithm search;
	int16 maxDepth = 0;

	// needs to return the next point from the given point on the given edge
	std::function<DataType(const DataType& fromPoint, const EdgeType& onEdge)> GetNextPointCallback;

	// needs to return all available edges from the given point
	std::function<TArray<EdgeType>(const DataType& fromPoint)>GetAvailableEdgesCallback;

	// needs to return true if the given point is the goal;
	std::function<bool(const DataType& point)> IsGoalCallback =
		[](const DataType&) { return false; };
};

class PathSearcher
{
public:
	template<class DataType, class EdgeType>
 static TSharedPtr<Tree<PathPoint<DataType>, EdgeType>> DFS(
     const PathSearcherInput<DataType, EdgeType>& inputData);

private:
	//returns true if reached goal
 template <class DataType, class EdgeType>
 static bool DFSStep(Tree<PathPoint<DataType>, EdgeType>& tree,
								     TSharedPtr<TreePoint<PathPoint<DataType>, EdgeType>> currentPoint,
                     const PathSearcherInput<DataType, EdgeType>& inputData,
                     int16 depth);
};

#pragma region Implementation

//returns true if reached goal
template <class DataType, class EdgeType>
bool PathSearcher::DFSStep(
			Tree<PathPoint<DataType>, EdgeType>& tree,
			TSharedPtr<TreePoint<PathPoint<DataType>, EdgeType>> currentPoint,
			const PathSearcherInput<DataType, EdgeType>& inputData,
			int16 depth)
{

	bool isGoalFound = false;

	if (inputData.IsGoalCallback(currentPoint->data.data)) {
    currentPoint->data.isToGoal = true;
		isGoalFound = true;
	}

	if (inputData.maxDepth > 0 && depth++ > inputData.maxDepth) {
		return false;
	}

	const auto edges = inputData.GetAvailableEdgesCallback(currentPoint->data.data);
	for (const auto edge : edges) {
		TSharedPtr<TreePoint<PathPoint<DataType>, EdgeType>> newPoint =
			TSharedPtr<TreePoint<PathPoint<DataType>, EdgeType>>{
				new TreePoint<PathPoint<DataType>, EdgeType>()};

		newPoint->data.data = inputData.GetNextPointCallback(currentPoint->data.data, edge);
		if (tree.Contains(newPoint->data,[](const PathPoint<DataType>& data1,
                         const PathPoint<DataType>& data2) {
														return data1.data == data2.data;})) {
			continue;
		}
		
		newPoint->parent = currentPoint;
		currentPoint->children[edge] = newPoint;
		if (DFSStep(tree, newPoint, inputData, depth)) {
			currentPoint->data.isToGoal = true;
			isGoalFound = true;
		}
	}

	return isGoalFound;
}

template <class DataType, class EdgeType>
TSharedPtr<Tree<PathPoint<DataType>, EdgeType>> PathSearcher::DFS(
    const PathSearcherInput<DataType, EdgeType>& inputData)
{
	using TreePathPointPtr = TSharedPtr<Tree<PathPoint<DataType>, EdgeType>>;
  TreePathPointPtr result{new Tree<PathPoint<DataType>, EdgeType>()};

  auto root = result->GetRoot(); 
  root->data = {inputData.startPoint.Key};
  for(const auto& edge : inputData.startPoint.Value) {
    auto newPoint = TSharedPtr<TreePoint<PathPoint<DataType>, EdgeType>>{
        new TreePoint<PathPoint<DataType>, EdgeType>};
    newPoint->parent = root;
    newPoint->data.data = {inputData.GetNextPointCallback(root->data.data, edge)};
    root->children[edge] = newPoint;
    if (DFSStep(*result, newPoint, inputData, 1)) break;
  }
	return result;
}

#pragma endregion

}