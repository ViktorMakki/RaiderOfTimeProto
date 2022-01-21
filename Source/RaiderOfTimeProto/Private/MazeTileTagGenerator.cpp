// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeTileTagGenerator.h"

#include <vector>

#include "MazePath.h"
#include "UtilsLibrary.h"

class Wall {
 public:
  FIntPoint start, end;

  void Draw(ATileMap* map) const {
    DrawWalls(map, start, end);
  }

  int32 distance(FIntPoint point) {
    int32 startDistance = (point - start).Size();
    int32 endDistance = (point - start).Size();
    return startDistance > endDistance ? endDistance : startDistance;
  }

  int32 Size() const {
    return start.X < end.X ? end.X - start.X : end.Y - start.Y;
  }

 private:
  static void DrawWalls(ATileMap* map, const FIntPoint& start,
                        const FIntPoint& end) {
    if (start.X == end.X)
      DrawWallsVertical(map, start.X, start.Y, end.Y);
    if (start.Y == end.Y)
      DrawWallsHorizontal(map, start.Y, start.X, end.X);
  }

  static void DrawWallsVertical(ATileMap* map, int32 x, int32 yStart, int32 yEnd)
	{
    for (int32 y = yStart; y <= yEnd; y++) {
      map->SetTileTag({x, y}, static_cast<int32>(MazeTileType::WALL));
    }
  }

  static void DrawWallsHorizontal(ATileMap* map, int32 y,
                                  int32 xStart, int32 xEnd)
	{
  	for (int32 x = xStart; x <= xEnd; x++) {
    	map->SetTileTag({x, y}, static_cast<int32>(MazeTileType::WALL));
    }
  }
};

class Chamber {
 public:
  FIntPoint leftBottom, rightTop;
  int32 Width() const { return rightTop.X - leftBottom.X; }

  int32 Height() const { return rightTop.Y - leftBottom.Y; }

  FIntPoint LeftTop() const { return {leftBottom.X, rightTop.Y}; }

  FIntPoint RightBottom() const { return {rightTop.X, leftBottom.Y}; }

  std::vector<Wall> GetWalls() const {
    std::vector<Wall> result{4};
    result[0] = {{leftBottom.X, rightTop.Y}, rightTop};    // up
    result[1] = {{rightTop.X, leftBottom.Y}, rightTop};    // right
    result[2] = {leftBottom, {rightTop.X, leftBottom.Y}};  // down
    result[3] = {leftBottom, {leftBottom.X, rightTop.Y}};  // left
    return result;
  }
};

class Gate {
 public:
  FIntPoint location;

  void Draw(ATileMap* map) const {
    map->SetTileTag(location, static_cast<int32>(MazeTileType::GATE));
  }
};

/** Gates that are on the same wall, splitting the same chamber*/
struct SiblingGates {
  Gate gate1;
  Gate gate2;
};
#pragma region Recursive Maze Generation

struct SplitChamberParameters {
  Chamber chamber;
  int32 recursionLevel;
  int32 minWallSize;
  int32 maxWallSize;
};

static bool IsHorizontal(const Chamber& chamber) {
  int32 width = chamber.Width();
  int32 height = chamber.Height();

  if (width > height) return true;
  if (width < height) return false;
  return FMath::RandBool();
}

static bool IsHorizontal(const Wall& wall) {
  if (wall.start.X != wall.end.X) return true;
  return false;
}

// returns the wall that splitted the chamber
static Wall CreateVerticalSplitWall(const Chamber& chamber) {
  int32 randomStart = chamber.Width() > 7 ? 3 : 1;
  // Walls can be on every second place to avoid blocking gates
  int32 splitX =
      FMath::RandRange(randomStart, (chamber.Width() - randomStart) / 2);
  int32 x = chamber.leftBottom.X + (2 * splitX);
  return {{x, chamber.leftBottom.Y}, {x, chamber.rightTop.Y}};
}

// returns the wall that splitted the chamber
static Wall CreateHorizontalSplitWall(const Chamber& chamber) {
  int32 randomStart = chamber.Width() > 7 ? 3 : 1;
  // Walls can be on every second place to avoid blocking gates
  int32 splitY =
      FMath::RandRange(randomStart, (chamber.Height() - randomStart) / 2);
  int32 y = chamber.leftBottom.Y + (2 * splitY);
  return {{chamber.leftBottom.X, y}, {chamber.rightTop.X, y}};
}

static Wall CreateSplitWall(const Chamber& chamber, bool isChamberHorizontal) {
  return isChamberHorizontal ? CreateVerticalSplitWall(chamber)
                             : CreateHorizontalSplitWall(chamber);
}

static Gate CreateGateOnWall(const Wall& wall) {
  int32 min = wall.Size() > 4 ? 1 : 0;
  int32 max = (wall.Size() - 1) / 2;
  int32 rand = FMath::RandRange(min, max) * 2;

  if (IsHorizontal(wall)) {
    int32 gateX = rand + 1 + wall.start.X;
    return {{gateX, wall.start.Y}};
  }
  int32 gateY = rand + 1 + wall.start.Y;
  return {{wall.start.X, gateY}};
}

static Gate CreateSecondGateOnWall(const Wall& wall, const Gate& otherGate) {
  if (IsHorizontal(wall)) {
    const Wall wallTemp1{wall.start,
                         {otherGate.location.X - 1, otherGate.location.Y}};
    const Wall wallTemp2{{otherGate.location.X + 1, otherGate.location.Y},
                         wall.end};
    return wallTemp1.Size() >= wallTemp2.Size() ? CreateGateOnWall(wallTemp1)
                                                : CreateGateOnWall(wallTemp2);
  }

  const Wall wallTemp1{wall.start,
                       {otherGate.location.X, otherGate.location.Y - 1}};
  const Wall wallTemp2{{otherGate.location.X, otherGate.location.Y + 1},
                       wall.end};
  return wallTemp1.Size() >= wallTemp2.Size() ? CreateGateOnWall(wallTemp1)
                                              : CreateGateOnWall(wallTemp2);
}

static bool ShouldCreateSecondGate(const Wall& wall, int32 startSize,
                                   int32 endSize) {
  const int32 size = wall.Size();

  return ((size < endSize) && (size > startSize)) &&
         // Can not add more gate if the chamber is smaller
         (size >= 5);
}

static void CreateGates(ATileMap* tiles,
                        TArray<SiblingGates>& siblingGates,
                        const Wall& splitWall,
                        const SplitChamberParameters& param) {
  const bool isHorizontal = IsHorizontal(splitWall);
  const Gate gate = CreateGateOnWall(splitWall);
  if (ShouldCreateSecondGate(splitWall, param.minWallSize, param.maxWallSize)) {
    const Gate secondGate = CreateSecondGateOnWall(splitWall, gate);
    siblingGates.Add({gate, secondGate});
  } else {
    siblingGates.Add({gate, gate});
  }
}

static void SplitChamber(ATileMap* tiles,
                         TArray<SiblingGates>& siblingGates,
                         SplitChamberParameters param) {
  if (param.chamber.Width() < 3 && param.chamber.Height() < 3) return;

  param.recursionLevel++;

  bool isHorizontal = IsHorizontal(param.chamber);

  const Wall splitWall = CreateSplitWall(param.chamber, isHorizontal);
  splitWall.Draw(tiles);

  CreateGates(tiles, siblingGates, splitWall, param);

  const Chamber splitChamber1 = {param.chamber.leftBottom, splitWall.end};
  const Chamber splitChamber2 = {splitWall.start, param.chamber.rightTop};

  param.chamber = splitChamber1;
  SplitChamber(tiles, siblingGates, param);

  param.chamber = splitChamber2;
  SplitChamber(tiles, siblingGates, param);
}

#pragma endregion

#pragma region Maze initialization

static void CreateBaseMap(ATileMap* TileMap, int32 width, int32 height) {
  for (int32 x = 0; x < width; x++) {
    for (int32 y = 0; y < height; y++) {
      if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
        TileMap->SetTileTag({x, y}, static_cast<int32>(MazeTileType::WALL));
      } else {
        TileMap->SetTileTag({x, y}, static_cast<int32>(MazeTileType::PATH));
      }
    }
  }
}

static FIntPoint RandomPathInChamber(const Chamber& chamber) {
  const  int32 distanceX = FMath::RandRange(0, (chamber.Width() - 1) / 2) * 2 + 1;
	const int32 distanceY = FMath::RandRange(0, (chamber.Height() - 1) / 2) * 2 + 1;

  return {chamber.leftBottom.X + distanceX, chamber.leftBottom.Y + distanceY};
}

static Chamber CreateGoalChamber(ATileMap* tiles,
                                 const Chamber& baseChamber, int32 goalWidth,
                                 int32 goalHeight) {
  int32 gWidth = (goalWidth % 2) == 0 ? goalWidth + 1 : goalWidth;
  int32 gHeight = (goalHeight % 2) == 0 ? goalHeight + 1 : goalHeight;

  int32 margin = 4;
  Chamber searchChamber{
      {baseChamber.leftBottom.X + margin, baseChamber.leftBottom.Y + margin},
      {baseChamber.rightTop.X - (gWidth + margin),
       baseChamber.rightTop.Y - (gHeight + margin)}};
  FIntPoint goalStart = RandomPathInChamber(searchChamber);

  for (int x = 0; x < gWidth; x++) {
    for (int y = 0; y < gHeight; y++) {
      tiles->SetTileTag(goalStart + FIntPoint{x, y},
                        static_cast<int32>(MazeTileType::GOAL));
    }
  }
  return {{goalStart.X - 1, goalStart.Y - 1},
          {goalStart.X + gWidth, goalStart.Y + gHeight}};
}

enum Direction { up = 0, right = 1, down = 2, left = 3 };

static std::vector<Chamber> CreateStartChambers(const Chamber& baseChamber,
                                                const Chamber& goalChamber) {
  std::vector<Chamber> chambers{8};
  chambers[0] = {goalChamber.LeftTop(),
                 {goalChamber.rightTop.X, baseChamber.rightTop.Y}};  // up
  chambers[1] = {goalChamber.rightTop, baseChamber.rightTop};        // upright
  chambers[2] = {goalChamber.RightBottom(),
                 {baseChamber.rightTop.X, goalChamber.rightTop.Y}};  // right
  chambers[3] = {
      {goalChamber.rightTop.X, baseChamber.leftBottom.Y},
      {baseChamber.rightTop.X, goalChamber.leftBottom.Y}};  // downright
  chambers[4] = {{goalChamber.leftBottom.X, baseChamber.leftBottom.Y},
                 goalChamber.RightBottom()};                       // down
  chambers[5] = {baseChamber.leftBottom, goalChamber.leftBottom};  // downleft
  chambers[6] = {{baseChamber.leftBottom.X, goalChamber.leftBottom.Y},
                 goalChamber.LeftTop()};  // left
  chambers[7] = {{baseChamber.leftBottom.X, goalChamber.rightTop.Y},
                 {goalChamber.leftBottom.X, baseChamber.rightTop.Y}};  // upleft
  return chambers;
}

static int8 RandomStartSpace(const std::vector<Chamber>& startChambers) {
  int8 result = FMath::RandRange(0, 3) * 2 + 1;
  while (startChambers[result].Width() < 3 ||
         startChambers[result].Height() < 3) {
    result = FMath::RandRange(0, 3) * 2 + 1;
  }
  return result;
}

static Gate CreateGoalGate(const Chamber& chamber, Direction direction) {
  switch (direction) {
    case up:
      return CreateGateOnWall(chamber.GetWalls()[Direction::down]);
    case left:
      return CreateGateOnWall(chamber.GetWalls()[Direction::right]);
    case right:
      return CreateGateOnWall(chamber.GetWalls()[Direction::left]);
    case down:
      return CreateGateOnWall(chamber.GetWalls()[Direction::up]);
    default:
      return {};
  }
}

static void CreateStartGatesClockwise(ATileMap* tiles,
                                      TArray<SiblingGates>& siblingGates,
                                      const std::vector<Chamber>& startChambers,
                                      const SplitChamberParameters& param,
                                      Direction startDirection)
{
  const int32 startIndex = startDirection * 2;
  Direction direction = static_cast<Direction>((startDirection + 1) % 4);
  for (int32 i = 0; i < 7; i++) {
    CreateGates(tiles,siblingGates, startChambers[(startIndex + i) % 8].GetWalls()[direction], param);
    direction = (i % 2 == 0) ? static_cast<Direction>((direction + 1) % 4) : direction;
  }
}

static void CreateStartGatesUnclockwise(ATileMap* tiles,
                                        TArray<SiblingGates>& siblingGates,
                                        const std::vector<Chamber>& startChambers,
                                        const SplitChamberParameters& param, Direction startDirection)
{
  const int32 startIndex = startDirection * 2;
  Direction direction = (startDirection - 1) < 0
                            ? static_cast<Direction>(3)
                            : static_cast<Direction>(startDirection - 1);
  for (int32 i = 0; i < 7; i++) {
    const int32 dif = startIndex - i;
    const int32 index = dif < 0 ? 8 + dif : dif;
    CreateGates(tiles, siblingGates, startChambers[index].GetWalls()[direction], param);
    direction = (i % 2 == 0) ? static_cast<Direction>((direction - 1) < 0 ? 3 : (direction - 1)) : direction;
  }
}

static void CreateStartGates(ATileMap* tiles,
                             TArray<SiblingGates>& siblingGates,
                             const std::vector<Chamber>& startChambers,
                             const SplitChamberParameters& param,
                             Direction startDirection, bool isClockwise) {
  isClockwise ? CreateStartGatesClockwise(tiles,siblingGates, startChambers, param, startDirection)
              : CreateStartGatesUnclockwise(tiles,siblingGates, startChambers, param, startDirection);
}

#pragma endregion

int32 Distance(const SiblingGates& gates) {
  return (gates.gate1.location - gates.gate2.location).Size();
}

TArray<SiblingGates> FilterByDistance(const TArray<SiblingGates>& gates,
                                       int32 minDistance, const FIntPoint& startSpace) {
  TArray<SiblingGates> result;
  for (const auto& gate : gates) {
    if( (Distance(gate) >= minDistance && 
      (startSpace - gate.gate1.location).Size() >= minDistance) && 
      (startSpace - gate.gate2.location).Size() >= minDistance){
        result.Add(gate);
    }
  }
  return result;
}

void GenerateMaze(ATileMap* tileMap, const FMazeTileGeneratorInput& input)
{
  TArray<SiblingGates> siblingGates;
  // Only can work with odd numbers
  const auto size = tileMap->Size();
  const int32 width = size.X;
  const int32 height = size.Y;

  CreateBaseMap(tileMap, width, height);

  Chamber firstChamber;
  firstChamber.leftBottom = {0, 0};
  firstChamber.rightTop = {width - 1, height - 1};

  const Chamber goalChamber = CreateGoalChamber( tileMap, firstChamber, input.goalWidth, input.goalHeight);

  std::vector<Chamber> startChambers =
      CreateStartChambers(firstChamber, goalChamber);
  const int8 startSpaceDirection = RandomStartSpace(startChambers);
  const FIntPoint startSpace = RandomPathInChamber(startChambers[startSpaceDirection]);

  bool isClockwiseGenerated = FMath::RandBool();
  const Direction startDirection =
      isClockwiseGenerated
          ? static_cast<Direction>(((startSpaceDirection / 2) + 1) % 4)
          : static_cast<Direction>((startSpaceDirection / 2));
  CreateStartGates(tileMap, siblingGates, startChambers,
                   {startChambers[0], 0, input.minWallSize, input.maxWallSize},
                   startDirection, isClockwiseGenerated);

  for (const auto& c : startChambers) {
    for (const auto& wall : c.GetWalls()) {
      if (wall.Size() < 2) continue;
      wall.Draw(tileMap);
    }
    SplitChamber(tileMap, siblingGates,
                 {c,1, input.minWallSize, input.maxWallSize});
  }

  // frist gate to goal
  const Gate goalGate = CreateGoalGate(startChambers[startDirection * 2], startDirection);
  tileMap->SetTileTag(goalGate.location, static_cast<int32>(MazeTileType::GOALGATE));

  for (const auto& gates : siblingGates) {
    tileMap->SetTileTag(gates.gate1.location, static_cast<int32>(MazeTileType::PATH));
    tileMap->SetTileTag(gates.gate2.location, static_cast<int32>(MazeTileType::PATH));
  }

  //Filter gates near to start
	auto filteredGates = FilterByDistance(siblingGates, input.minSiblingGateDistance, startSpace);
  Shuffle(filteredGates);

  for (int32 i = 0; i < input.gateLayerCount; i++) {
    if (i >= filteredGates.Num()) break;
    filteredGates[i].gate1.Draw(tileMap);
    filteredGates[i].gate2.Draw(tileMap);
  }

	const auto path = UMazePath::Create(tileMap, goalGate.location);
  const auto pathToGoal = path->GetPathToGoal();
	if (pathToGoal.Num() < 2) return;
  const auto start = pathToGoal[pathToGoal.Num() - 1].location;
  tileMap->SetTileTag(start, static_cast<int32>(MazeTileType::START));
}

void AMazeTileTagGenerator::Destruct()
{
  if (!tileMap) return;
	tileMap->Clear();
}

void AMazeTileTagGenerator::Construct() {
  if (!tileMap) return;
	Destruct();
  //Maze size has to be odd
	tileMap->Create();
	const auto size = tileMap->Size();
  int32 width = size.X % 2 == 0 ? size.X + 1 : size.X;
  int32 height = size.Y % 2 == 0 ? size.Y + 1 : size.Y;
  width = FMath::Max(width, 11);
  height = FMath::Max(height, 11);
  tileMap->SetSize({width, height});

  GenerateMaze(tileMap, input);
}
