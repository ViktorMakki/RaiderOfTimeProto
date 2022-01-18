// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generator.h"
#include "TileMap.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MazeTileTagGenerator.generated.h"


USTRUCT(BlueprintType)
struct FMazeTileGeneratorInput {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  int32 goalWidth = 3;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  int32 goalHeight = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  int32 gateLayerCount;

	/**From what wall size is enabled to make double doors*/
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  int32 maxWallSize = 50;

	/**From what wall size is enabled to make double doors*/
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  int32 minWallSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  int32 minSiblingGateDistance;

};

UCLASS(Blueprintable)
class RAIDEROFTIMEPROTO_API AMazeTileTagGenerator : public AGenerator
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  ATileMap* tileMap;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
  FMazeTileGeneratorInput input;
  
  virtual void Destruct() override;

  virtual void Construct() override;
};
