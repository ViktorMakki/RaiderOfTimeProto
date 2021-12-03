// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"

#include <vector>


class Wall
{
public:
	FIntPoint start, end;

	void Draw(TArray<FTileArray>& map, int32 recursionLevel) const
	{
		DrawWalls(map, start, end, recursionLevel);
	}

	int32 distance(FIntPoint point) 
	{
		int32 startDistance = (point - start).Size();
		int32 endDistance = (point - start).Size();
		return startDistance > endDistance ? endDistance : startDistance;
	}

	int32 Size() const
	{
		return start.X < end.X ? end.X - start.X : end.Y - start.Y;
	}

private:
	static void DrawWalls(TArray<FTileArray>& map, const FIntPoint& start, const FIntPoint& end, int32 recursionLevel)
	{
		if (start.X == end.X)
			DrawWallsVertical(map, start.X, start.Y, end.Y, recursionLevel);
		if (start.Y == end.Y)
			DrawWallsHorizontal(map, start.Y, start.X, end.X, recursionLevel);
	}

	static void DrawWallsVertical(TArray<FTileArray>& map, int32 x, int32 yStart, int32 yEnd, int32 recursionLevel)
	{
		for (int32 y = yStart; y <= yEnd; y++) {
			map[x].tiles[y].tile = MazeTileType::WALL;
			map[x].tiles[y].recursionLevel = recursionLevel;
		}
	}

	static void DrawWallsHorizontal(TArray<FTileArray>& map, int32 y, int32 xStart, int32 xEnd, int32 recursionLevel)
	{
		for (int32 x = xStart; x <= xEnd; x++) {
			map[x].tiles[y].tile = MazeTileType::WALL;
			map[x].tiles[y].recursionLevel = recursionLevel;
		}
	}
};


class Chamber
{
public:
	FIntPoint leftBottom, rightTop;
	int32 Width() const
	{
		return rightTop.X - leftBottom.X;
	}

	int32 Height() const
	{
		return rightTop.Y - leftBottom.Y;
	}

	FChamber Cast(int32 recursionLevel) const
	{
		return { leftBottom, rightTop, recursionLevel };
	}

	FIntPoint LeftTop() const
	{
		return {leftBottom.X, rightTop.Y};
	}

	FIntPoint RightBottom() const
	{
		return {rightTop.X, leftBottom.Y};
	}

	std::vector<Wall> GetWalls() const 
	{
		std::vector<Wall> result{ 4 };
		result[0] = { {leftBottom.X, rightTop.Y }, rightTop };	// up
		result[1] = { {rightTop.X, leftBottom.Y }, rightTop };	// right
		result[2] = { leftBottom, {rightTop.X, leftBottom.Y} }; // down
		result[3] = { leftBottom, {leftBottom.X, rightTop.Y} }; // left
		return result;
	}
};

class Door
{
public:
	FIntPoint location;

	void Draw(TArray<FTileArray>& map, int32 recursionLevel) const
	{
		map[location.X].tiles[location.Y].tile = MazeTileType::DOOR;
		map[location.X].tiles[location.Y].recursionLevel = recursionLevel;
	}

	FDoor Cast(Chamber chamber, bool isHorizontal, int32 recursionLevel) const
	{
		return { location, isHorizontal, chamber.Cast(recursionLevel),  recursionLevel };
	}
};

#pragma region Recursive Maze Generation

struct SplitChamberParameters
{
	Chamber chamber;
	int32 recursionLevel;
	int32 circleSizeStart;
	int32 circleSizeEnd;
};

static bool IsHorizontal(const Chamber& chamber)
{
	int32 width = chamber.Width();
	int32 height = chamber.Height();

	if (width > height)
		return true;
	if (width < height)
		return false;
	return FMath::RandBool();
}

static bool IsHorizontal(const Wall& wall)
{
	if (wall.start.X != wall.end.X)
		return true;
	return false;
}

//returns the wall that splitted the chamber
static Wall CreateVerticalSplitWall(const Chamber& chamber)
{
	int32 randomStart = chamber.Width() > 7 ? 3 : 1;
	//Walls can be on every second place to avoid blocking doors
	int32 splitX = FMath::RandRange(randomStart, (chamber.Width() - randomStart) / 2);
	int32 x = chamber.leftBottom.X + (2 * splitX);
	return { { x, chamber.leftBottom.Y}, {x, chamber.rightTop.Y} };
}

//returns the wall that splitted the chamber
static Wall CreateHorizontalSplitWall(const Chamber& chamber)
{
	int32 randomStart = chamber.Width() > 7 ? 3 : 1;
	//Walls can be on every second place to avoid blocking doors
	int32 splitY = FMath::RandRange(randomStart, (chamber.Height() - randomStart) / 2);
	int32 y = chamber.leftBottom.Y + (2 * splitY);
	return { { chamber.leftBottom.X, y}, {chamber.rightTop.X, y} };
}

static Wall CreateSplitWall(const Chamber& chamber, bool isChamberHorizontal)
{
	return isChamberHorizontal ? CreateVerticalSplitWall(chamber) : CreateHorizontalSplitWall(chamber);
}

static Door CreateDoorOnWall(const Wall& wall)
{
	int32 min = wall.Size() > 4 ? 1 : 0;
	int32 max = (wall.Size() - 1) / 2;
	int32 rand = FMath::RandRange(min, max) * 2;

	if (IsHorizontal(wall)) {
		int32 doorX = rand + 1 + wall.start.X;
		return { {doorX, wall.start.Y} };
	}
	int32 doorY = rand + 1 + wall.start.Y;
	return { {wall.start.X, doorY} };
}

static Door CreateSecondDoorOnWall(const Wall& wall, const Door& otherDoor) 
{
	if(IsHorizontal(wall)) {
		const Wall wallTemp1{ wall.start, {otherDoor.location.X - 1, otherDoor.location.Y} };
		const Wall wallTemp2{ {otherDoor.location.X + 1, otherDoor.location.Y}, wall.end };		
		return wallTemp1.Size() >= wallTemp2.Size() ? CreateDoorOnWall(wallTemp1) : CreateDoorOnWall(wallTemp2);
	}

	const Wall wallTemp1{ wall.start, {otherDoor.location.X, otherDoor.location.Y - 1} };
	const Wall wallTemp2{ {otherDoor.location.X, otherDoor.location.Y + 1}, wall.end };
	return wallTemp1.Size() >= wallTemp2.Size() ? CreateDoorOnWall(wallTemp1) : CreateDoorOnWall(wallTemp2);
}

static bool ShouldCreateSecondDoor(const Chamber& chamber, int32 startSize, int32 endSize) 
{
	int32 width = chamber.Width();
	int32 height = chamber.Height();

	return	(width <= startSize && width >= endSize) &&
			(height <= startSize && height >= endSize) &&
			// Can not add more door if the chamber is smaller
			(width >= 5 && height >= 5);
}

static void CreateDoors(FMazeGenerationResult& result,
						const Wall& splitWall,
						const SplitChamberParameters& param)
{
	const bool isHorizontal = IsHorizontal(param.chamber);
	const Door door = CreateDoorOnWall(splitWall);
	const FDoor fDoor = door.Cast(param.chamber, isHorizontal, param.recursionLevel);
	door.Draw(result.tiles, param.recursionLevel);
	result.doors.Add(fDoor);

	if (ShouldCreateSecondDoor(param.chamber, param.circleSizeStart, param.circleSizeEnd)) {
		const Door secondDoor = CreateSecondDoorOnWall(splitWall, door);
		secondDoor.Draw(result.tiles, param.recursionLevel);
		const FDoor secondFDoor = secondDoor.Cast(param.chamber, isHorizontal, param.recursionLevel);
		result.doors.Add(secondFDoor);
		result.siblingDoors.Add({ fDoor, secondFDoor });
	}

}

static void SplitChamber(FMazeGenerationResult& result, SplitChamberParameters param)
{
	if (param.chamber.Width() < 3 && param.chamber.Height() < 3)
		return;

	param.recursionLevel++;

	result.chambers.Add(param.chamber.Cast(param.recursionLevel));

	bool isHorizontal = IsHorizontal(param.chamber);

	const Wall splitWall = CreateSplitWall(param.chamber, isHorizontal);
	splitWall.Draw(result.tiles, param.recursionLevel);

	CreateDoors(result, splitWall, param);

	const Chamber splitChamber1 = { param.chamber.leftBottom, splitWall.end };
	const Chamber splitChamber2 = { splitWall.start, param.chamber.rightTop };

	param.chamber = splitChamber1;
	SplitChamber(result, param);

	param.chamber = splitChamber2;
	SplitChamber(result, param);
}

#pragma endregion

#pragma region Maze initialization

static TArray<FTileArray> CreateBaseMap(int32 width, int32 height)
{
	TArray<FTileArray> result;
	for (int32 x = 0; x < width; x++) {		
		result.Add({});
		for (int32 y = 0; y < height; y++) {
			result[x].tiles.Add({});
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
				result[x].tiles[y].tile = MazeTileType::WALL;
				result[x].tiles[y].recursionLevel = 0;
			}
			else {
				result[x].tiles[y].tile = MazeTileType::PATH;
				result[x].tiles[y].recursionLevel = 0;
			}
		}	
	}
	return result;
}

static FIntPoint RandomPathInChamber(const Chamber& chamber)
{
	int32 distanceX = FMath::RandRange(0, (chamber.Width() - 1) / 2) * 2 + 1;
	int32 distanceY = FMath::RandRange(0, (chamber.Height() - 1) / 2) * 2 + 1;

	return { chamber.leftBottom.X + distanceX,  chamber.leftBottom.Y + distanceY};
}

static Chamber CreateGoalChamber(TArray<FTileArray>& tiles, const Chamber& baseChamber, int32 goalWidth, int32 goalHeight)
{
	int32 gWidth = (goalWidth) % 2 == 0 ? goalWidth + 1 : goalWidth;
	int32 gHeight = (goalHeight) % 2 == 0 ? goalHeight + 1 : goalHeight;

	int32 margin = 4;
	Chamber searchChamber{ {baseChamber.leftBottom.X + margin, baseChamber.leftBottom.Y + margin }, { baseChamber.rightTop.X - (gWidth + margin), baseChamber.rightTop.Y - (gHeight + margin) }
};
	FIntPoint goalStart = RandomPathInChamber(searchChamber);

	for (int x = 0; x < gWidth; x++) {
		for (int y = 0; y < gHeight; y++) {
			tiles[x].tiles[y].tile = MazeTileType::GOAL;
		}
	}
	return { {goalStart.X - 1, goalStart.Y - 1}, {goalStart.X + gWidth, goalStart.Y + gHeight} };
}

enum Direction { up = 0, right = 1, down = 2, left = 3};

static std::vector<Chamber> CreateStartChambers(const Chamber& baseChamber, const Chamber& goalChamber) 
{
	std::vector<Chamber> chambers{ 8 };
	chambers[0] = { goalChamber.LeftTop(), {goalChamber.rightTop.X, baseChamber.rightTop.Y} };		//up
	chambers[1] = { goalChamber.rightTop, baseChamber.rightTop };	//upright 
	chambers[2] = { goalChamber.RightBottom(), {baseChamber.rightTop.X, goalChamber.rightTop.Y} };		//right
	chambers[3] = { {goalChamber.rightTop.X, baseChamber.leftBottom.Y }, {baseChamber.rightTop.X, goalChamber.leftBottom.Y} }; //downright
	chambers[4] = { {goalChamber.leftBottom.X, baseChamber.leftBottom.Y}, goalChamber.RightBottom() };	//down
	chambers[5] = { baseChamber.leftBottom, goalChamber.leftBottom }; // downleft
	chambers[6] = { {baseChamber.leftBottom.X, goalChamber.leftBottom.Y}, goalChamber.LeftTop() };	//left
	chambers[7] = { {baseChamber.leftBottom.X, goalChamber.rightTop.Y},{goalChamber.leftBottom.X, baseChamber.rightTop.Y} }; //upleft
	return chambers;
}

static int8 RandomStartSpace(const std::vector<Chamber>& startChambers) 
{
	int8 result = FMath::RandRange(0, 3) * 2 + 1;
	while (startChambers[result].Width() < 3 || startChambers[result].Height() < 3) {
		result = FMath::RandRange(0, 3) * 2 + 1;
	}
	return result;
}

static Door CreateGoalDoor(const Chamber& chamber, Direction direction)
{
	switch (direction)
	{
	case up: 
		return CreateDoorOnWall(chamber.GetWalls()[Direction::down]);
	case left:
		return CreateDoorOnWall(chamber.GetWalls()[Direction::right]);
	case right:
		return CreateDoorOnWall(chamber.GetWalls()[Direction::left]);
	case down:
		return CreateDoorOnWall(chamber.GetWalls()[Direction::up]);
	default:
		return {};
	}
}

static std::vector<Door> CreateStartDoorsClockwise(const std::vector<Chamber>& startChambers, Direction startDirection)
{
	std::vector<Door> result{ 8 };
	int32 startIndex = startDirection * 2;
	result[0] = CreateGoalDoor(startChambers[startIndex], startDirection);

	Direction direction = static_cast<Direction>((startDirection + 1) % 4);
	for (int32 i = 0; i < 7; i++) {
		result[i + 1] = CreateDoorOnWall(startChambers[(startIndex + i) % 8].GetWalls()[direction]);
		direction = ( i % 2 == 0 )? static_cast<Direction>((direction + 1) % 4) : direction;
	}
	return result;
}

static std::vector<Door> CreateStartDoorsUnclockwise(const std::vector<Chamber>& startChambers, Direction startDirection)
{
	std::vector<Door> result{ 8 };
	int32 startIndex = startDirection * 2;
	result[0] = CreateGoalDoor(startChambers[startIndex], startDirection);

	Direction direction = (startDirection - 1) < 0 ? static_cast<Direction>(3) : static_cast<Direction>(startDirection - 1);
	for (int32 i = 0; i < 7; i++) {
		int32 dif = startIndex - i;
		int32 index = dif < 0 ? 8 + dif : dif;
		result[i + 1] = CreateDoorOnWall(startChambers[index].GetWalls()[direction]);
		direction = (i % 2 == 0) ? static_cast<Direction>((direction - 1) < 0 ? 3 : (direction - 1)) : direction;
	}
	return result;
}

static std::vector<Door> CreateStartDoors(const std::vector<Chamber>& startChambers, Direction startDirection) 
{
	return FMath::RandBool() ? CreateStartDoorsClockwise(startChambers, startDirection) :
							   CreateStartDoorsUnclockwise(startChambers, startDirection);
}

#pragma endregion

FMazeGenerationResult UMazeGenerator::GenerateMaze(const FMazeGeneratorConstructData& data)
{
	// Only can work with odd numbers
	int32 width = data.mazeWidth % 2 == 0 ? data.mazeWidth + 1 : data.mazeWidth;
	int32 height = data.mazeHeight % 2 == 0 ? data.mazeHeight + 1 : data.mazeHeight;

	FMazeGenerationResult result;
	result.tiles = CreateBaseMap(width, height);

	Chamber firstChamber;
	firstChamber.leftBottom = { 0, 0 };
	firstChamber.rightTop = { width - 1, height - 1 };

	Chamber goalChamber = CreateGoalChamber(result.tiles, firstChamber, data.goalWidth, data.goalHeight);

	std::vector<Chamber> startChambers = CreateStartChambers(firstChamber, goalChamber);
	int8 startDir = RandomStartSpace(startChambers);
	FIntPoint startSpace = RandomPathInChamber(startChambers[startDir]);
	result.tiles[startSpace.X].tiles[startSpace.Y].tile = MazeTileType::START;
	std::vector<Door> startDoors = CreateStartDoors(startChambers, static_cast<Direction>(startDir /2));
	
	for (const auto& c : startChambers) {
		for (const auto& wall : c.GetWalls()) {
			if (wall.Size() < 2)
				continue;
			wall.Draw(result.tiles, 1);
		}
		SplitChamber(result,
			{ c, 1, data.CircleSizeStart, data.CircleSizeEnd });
	}

	for (const auto door : startDoors) {
		if (door.location == FIntPoint{0,0})
			continue;
		result.doors.Add(door.Cast(firstChamber, true, 1));
		door.Draw(result.tiles, 1);
	}

	return result;
}

bool UMazeGenerator::IsTypeOf(MazeTileType child, MazeTileType parent)
{
	return (child & parent) == parent;
}
