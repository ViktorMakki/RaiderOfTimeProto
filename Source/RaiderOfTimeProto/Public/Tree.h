// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "unordered_map"
#include "functional"

struct IDObject
{
  IDObject() : id(nextId++) {}

  bool operator==(const IDObject& other) const { return id == other.id; }

  virtual ~IDObject(){}
 private:
	int32 id;
	static int32 nextId;
};

int32 IDObject::nextId = 0;

namespace Graph
{

template <class DataType, class EdgeType>
struct TreePoint;

template <class DataType, class EdgeType>
struct TreePoint : public IDObject{
	DataType data;
  std::unordered_map<EdgeType, TSharedPtr<TreePoint<DataType, EdgeType>>> children;
	TSharedPtr<TreePoint<DataType, EdgeType>> parent;

  bool IsLeaf() const { return children.size() == 0; }

	EdgeType GetEdgeToParent() const
  {
    if (!parent) return {};
  	for (const auto& pair : parent->children) {
  		if (*pair.second == *this) return pair.first;
		}
  	return {};
  }

  TArray<EdgeType> GetEdgesToChildren() const
	{
  	TArray<EdgeType> result;
    for (const auto& pair : children) {
    	result.Add(pair.first);
    }
  	return result;
  }
};

template <class DataType, class EdgeType>
class Tree {
public:
	using IsEqualCallback = std::function<bool(const DataType& data1, const DataType& data2)>;

  // return true if it should brake
	using ForEachCallback = std::function<bool(TreePoint<DataType, EdgeType>& data)>;

	using ForEachCallbackConst = std::function<bool(const TreePoint<DataType, EdgeType>& data)>;

	using ForEachPtrCallback = std::function<bool(TSharedPtr<TreePoint<DataType, EdgeType>> data)>;

	void ForEach(const ForEachCallback& forEachCallback);

	void ForEach(const ForEachCallbackConst& forEachCallback) const;

	void ForEach(const ForEachPtrCallback& forEachCallback);

  void ForEachToRoot(const ForEachCallback& forEachCallback, TreePoint<DataType, EdgeType>& point);

	void ForEachToRoot(const ForEachCallbackConst& forEachCallback,
                     const TreePoint<DataType, EdgeType>& point) const;
  
	TSharedPtr<TreePoint<DataType, EdgeType>> Find(const DataType& data,
								const IsEqualCallback& isEqualCallback =
	                [](const DataType& data1, const DataType& data2) {
	                  return data1 == data2;
	                });

	bool Contains(const DataType& data, 
								const IsEqualCallback& isEqualCallback =
									[](const DataType& data1, const DataType& data2) {
									return data1 == data2;}) const;

	TSharedPtr<TreePoint<DataType, EdgeType>> GetRoot();

  TSharedPtr<TreePoint<DataType, EdgeType>> GetDeepestLeaf();

private:
  TSharedPtr<TreePoint<DataType, EdgeType>> root =
     TSharedPtr<TreePoint<DataType, EdgeType>>{
         new TreePoint<DataType, EdgeType>()};
};

template <class DataType, class EdgeType>
bool ForEachStepConst(
    const std::function<bool(const TreePoint<DataType, EdgeType>& data)>& forEachCallback,
    const TreePoint<DataType, EdgeType>& point)
{
  if (forEachCallback(point)) return true;

  for (const auto item : point.children) {
    if (!item.second) continue;
    if (ForEachStepConst(forEachCallback, *item.second)) return true;
  }
  return false;
}

template <class DataType, class EdgeType>
bool ForEachStep(const std::function<bool(TreePoint<DataType, EdgeType>& data)>& forEachCallback,
                 TreePoint<DataType, EdgeType>& point)
{
  if (forEachCallback(point)) return true;

  for (auto item : point.children) {
    if (!item.second)
      continue;
    if (ForEachStep(forEachCallback, *item.second)) return true;
  }
  return false;
}

template <class DataType, class EdgeType>
bool ForEachPtrStep(const std::function<bool(TSharedPtr<TreePoint<DataType, EdgeType>> data)>& forEachCallback,
TSharedPtr<TreePoint<DataType, EdgeType>> point) {
  if (forEachCallback(point)) return true;

  for (auto item : point->children) {
    if (!item.second) continue;
    if (ForEachPtrStep(forEachCallback, item.second)) return true;
  }
  return false;
}

template <class DataType, class EdgeType>
void Tree<DataType, EdgeType>::ForEach(const ForEachCallback& forEachCallback)
{
  ForEachStep(forEachCallback, *root);
}

template <class DataType, class EdgeType>
void Tree<DataType, EdgeType>::ForEach(const ForEachCallbackConst& forEachCallback) const
{
  ForEachStepConst(forEachCallback, *root);
}

template <class DataType, class EdgeType>
void Tree<DataType, EdgeType>::ForEach(const ForEachPtrCallback& forEachCallback)
{
  ForEachPtrStep(forEachCallback, root);
}


template <class DataType, class EdgeType>
bool ForEachToRootStepConst(
    const std::function<bool(const TreePoint<DataType, EdgeType>& data)>&
        forEachCallback,
             const TreePoint<DataType, EdgeType>& root,
             const TreePoint<DataType, EdgeType>& point) {
  if(forEachCallback(point)) return true;
  if (!point.parent) return true;
  if (ForEachToRootStepConst(forEachCallback, root, *point.parent)) return true;
  return false;
}

template <class DataType, class EdgeType>
bool ForEachToRootStep(const std::function<bool(TreePoint<DataType, EdgeType>& data)>& forEachCallback,
    const TreePoint<DataType, EdgeType>& root,
    TreePoint<DataType, EdgeType>& point) {
  if (forEachCallback(point)) return true;
  if (!point.parent) return true;
  if (ForEachToRootStep(forEachCallback, root, *point.parent)) return true;
  return false;
}

template <class DataType, class EdgeType>
void Tree<DataType, EdgeType>::ForEachToRoot(
    const ForEachCallback& forEachCallback,
    TreePoint<DataType, EdgeType>& point) {
  ForEachToRootStep(forEachCallback, *root, point);
}

template <class DataType, class EdgeType>
void Tree<DataType, EdgeType>::ForEachToRoot(const ForEachCallbackConst& forEachCallback,
	const TreePoint<DataType, EdgeType>& point) const
{
  ForEachToRootStepConst(forEachCallback, *root, point);
}

template <class DataType, class EdgeType>
TSharedPtr<TreePoint<DataType, EdgeType>> Tree<DataType, EdgeType>::Find(const DataType& data, const IsEqualCallback& isEqualCallback)
{
  TSharedPtr<TreePoint<DataType, EdgeType>> result;
  ForEach([&data, &result, &isEqualCallback](const TreePoint<DataType, EdgeType>& data2) {
    if (isEqualCallback(data, data2.data)) {
      result = data2;
      return true;
    }
    return false;
  });
  return result;
}

template <class DataType, class EdgeType>
bool Tree<DataType, EdgeType>::Contains(const DataType& data, const IsEqualCallback& isEqualCallback) const
{
  bool isFound = false;
  ForEach([&data, &isFound, &isEqualCallback](const TreePoint<DataType, EdgeType>& data2)
  {
  	if (isEqualCallback(data, data2.data)) {
      isFound = true;
  		return true;
  	}
    return false;
  });
  return isFound;
}

template <class DataType, class EdgeType>
TSharedPtr<TreePoint<DataType, EdgeType>> Tree<DataType, EdgeType>::GetRoot() {
  return root;
}

template <class DataType, class EdgeType>
TSharedPtr<TreePoint<DataType, EdgeType>> Tree<DataType, EdgeType>::GetDeepestLeaf() {
  TSharedPtr<TreePoint<DataType, EdgeType>> result = root;
  int32 depth = 0;
  ForEach([&](TSharedPtr<TreePoint<DataType, EdgeType>> point)
  {
    if (point->IsLeaf()) {
      int32 depthTemp = 0;
      ForEachToRoot(
          [&depthTemp](const TreePoint<DataType, EdgeType>&) {
            depthTemp++;
            return false;
          },
          *point);
      if (depthTemp > depth) {
        depth = depthTemp;
        result = point;
      }
    }
  	return false;
  });

  return result;
}
}
