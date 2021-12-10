// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

namespace PathSearching {

template<class PointType, class EdgeType>
struct Point
{
	PointType data;
	std::vector<EdgeType> edges;
};

template <class PointType, class EdgeType>
struct PathPoint {
  Point<PointType, EdgeType> point;
  int32 distance;
};


template<class PointType, class EdgeType>
struct PathSearchResult 
{
	//path starts with goal and ends with the start point
	//Contains points with 1 edge
  std::vector<PathPoint<PointType, EdgeType>> pathToGoal;
  std::vector<PathPoint<PointType, EdgeType>> walkedPoints;
};

template<class PointType, class EdgeType>
struct PathSearcherInput 
{
	// starting point with available edges
	Point<PointType, EdgeType> startPoint;

	//How deep should the algorithm search;
	int16 maxDepth = 0;

	// needs to return the next point from the given point on the given edge, with all available edges
	std::function<Point<PointType, EdgeType>(const PointType& fromPoint, const EdgeType& onEdge)> GetNextPointCallback;

	// needs to return true if the given point is the goal;
	std::function<bool (const PointType& point)> IsGoalCallback;
};

class PathSearcher
{
public:
	template<class PointType, class EdgeType>
	static PathSearchResult<PointType, EdgeType> DFS(const PathSearcherInput<PointType, EdgeType>& inputData);
private:
	//returns true if reached goal
	template<class PointType, class EdgeType>
	static bool DFSStep(PathSearchResult<PointType, EdgeType>& result, const PathSearcherInput<PointType, EdgeType>& inputData, const Point<PointType, EdgeType>& currentPoint, int16 depth);
};

#pragma region Implementation

//returns true if reached goal
template<class PointType, class EdgeType>
inline bool PathSearcher::DFSStep(PathSearchResult<PointType, EdgeType>& result, const PathSearcherInput<PointType, EdgeType>& inputData, const Point<PointType, EdgeType>& currentPoint, int16 depth)
{	
	if (std::find_if(result.walkedPoints.begin(), result.walkedPoints.end(),
		[&currentPoint](const PathPoint<PointType, EdgeType>& point) { return point.point.data == currentPoint.data; }) != result.walkedPoints.end()) {
		return false;
	}

	if (inputData.maxDepth > 0 && depth > inputData.maxDepth)
		return false;

	depth++;
        result.walkedPoints.push_back({currentPoint, depth});

	if (inputData.IsGoalCallback(currentPoint.data)) {
		result.pathToGoal.push_back({{currentPoint.data, {}}, depth});
		return true;
	}

	//OPTIMIZATION: dont check the edge it came from
	for (const auto& edge : currentPoint.edges) {
		const auto nextPoint = inputData.GetNextPointCallback(currentPoint.data, edge);
		if (DFSStep(result, inputData, nextPoint, depth)) {
                  result.pathToGoal.push_back({{currentPoint.data, {edge}}, depth});
			return true;
		}
	}
	return false;
}

template<class PointType, class EdgeType>
inline PathSearchResult<PointType, EdgeType> PathSearcher::DFS(const PathSearcherInput<PointType, EdgeType>& inputData)
{
	PathSearchResult<PointType, EdgeType> result;
	DFSStep(result, inputData, inputData.startPoint, 0);
	return result;
}

#pragma endregion

}