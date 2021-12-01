// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FMazeGeneratorData;
struct FTileArray;
#ifdef RAIDEROFTIMEPROTO_MazeGenerator_generated_h
#error "MazeGenerator.generated.h already included, missing '#pragma once' in MazeGenerator.h"
#endif
#define RAIDEROFTIMEPROTO_MazeGenerator_generated_h

#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_38_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FMazeGeneratorData_Statics; \
	RAIDEROFTIMEPROTO_API static class UScriptStruct* StaticStruct();


template<> RAIDEROFTIMEPROTO_API UScriptStruct* StaticStruct<struct FMazeGeneratorData>();

#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_28_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTileArray_Statics; \
	RAIDEROFTIMEPROTO_API static class UScriptStruct* StaticStruct();


template<> RAIDEROFTIMEPROTO_API UScriptStruct* StaticStruct<struct FTileArray>();

#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_SPARSE_DATA
#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGenerateMaze);


#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGenerateMaze);


#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMazeGenerator(); \
	friend struct Z_Construct_UClass_UMazeGenerator_Statics; \
public: \
	DECLARE_CLASS(UMazeGenerator, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/RaiderOfTimeProto"), NO_API) \
	DECLARE_SERIALIZER(UMazeGenerator)


#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_INCLASS \
private: \
	static void StaticRegisterNativesUMazeGenerator(); \
	friend struct Z_Construct_UClass_UMazeGenerator_Statics; \
public: \
	DECLARE_CLASS(UMazeGenerator, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/RaiderOfTimeProto"), NO_API) \
	DECLARE_SERIALIZER(UMazeGenerator)


#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMazeGenerator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMazeGenerator) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMazeGenerator); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMazeGenerator); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMazeGenerator(UMazeGenerator&&); \
	NO_API UMazeGenerator(const UMazeGenerator&); \
public:


#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMazeGenerator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMazeGenerator(UMazeGenerator&&); \
	NO_API UMazeGenerator(const UMazeGenerator&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMazeGenerator); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMazeGenerator); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMazeGenerator)


#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_PRIVATE_PROPERTY_OFFSET
#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_47_PROLOG
#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_PRIVATE_PROPERTY_OFFSET \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_SPARSE_DATA \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_RPC_WRAPPERS \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_INCLASS \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_PRIVATE_PROPERTY_OFFSET \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_SPARSE_DATA \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_RPC_WRAPPERS_NO_PURE_DECLS \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_INCLASS_NO_PURE_DECLS \
	RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h_50_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RAIDEROFTIMEPROTO_API UClass* StaticClass<class UMazeGenerator>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID RaiderOfTimeProto_Source_RaiderOfTimeProto_Public_MazeGenerator_h


#define FOREACH_ENUM_MAZETILETYPE(op) \
	op(MazeTileType::PATH) \
	op(MazeTileType::WALL) 

enum class MazeTileType : uint8;
template<> RAIDEROFTIMEPROTO_API UEnum* StaticEnum<MazeTileType>();

#define FOREACH_ENUM_MAZEPATHDIRECTION(op) \
	op(MazePathDirection::DOWN) \
	op(MazePathDirection::LEFT) \
	op(MazePathDirection::UP) \
	op(MazePathDirection::RIGHT) 

enum class MazePathDirection : uint8;
template<> RAIDEROFTIMEPROTO_API UEnum* StaticEnum<MazePathDirection>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
