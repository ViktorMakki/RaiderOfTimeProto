// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RaiderOfTimeProto/Public/MazeGenerator.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMazeGenerator() {}
// Cross Module References
	RAIDEROFTIMEPROTO_API UEnum* Z_Construct_UEnum_RaiderOfTimeProto_MazeTileType();
	UPackage* Z_Construct_UPackage__Script_RaiderOfTimeProto();
	RAIDEROFTIMEPROTO_API UEnum* Z_Construct_UEnum_RaiderOfTimeProto_MazePathDirection();
	RAIDEROFTIMEPROTO_API UScriptStruct* Z_Construct_UScriptStruct_FMazeGeneratorData();
	RAIDEROFTIMEPROTO_API UScriptStruct* Z_Construct_UScriptStruct_FTileArray();
	RAIDEROFTIMEPROTO_API UClass* Z_Construct_UClass_UMazeGenerator_NoRegister();
	RAIDEROFTIMEPROTO_API UClass* Z_Construct_UClass_UMazeGenerator();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
// End Cross Module References
	static UEnum* MazeTileType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_RaiderOfTimeProto_MazeTileType, Z_Construct_UPackage__Script_RaiderOfTimeProto(), TEXT("MazeTileType"));
		}
		return Singleton;
	}
	template<> RAIDEROFTIMEPROTO_API UEnum* StaticEnum<MazeTileType>()
	{
		return MazeTileType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_MazeTileType(MazeTileType_StaticEnum, TEXT("/Script/RaiderOfTimeProto"), TEXT("MazeTileType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_RaiderOfTimeProto_MazeTileType_Hash() { return 271322476U; }
	UEnum* Z_Construct_UEnum_RaiderOfTimeProto_MazeTileType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_RaiderOfTimeProto();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("MazeTileType"), 0, Get_Z_Construct_UEnum_RaiderOfTimeProto_MazeTileType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UECodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "MazeTileType::PATH", (int64)MazeTileType::PATH },
				{ "MazeTileType::WALL", (int64)MazeTileType::WALL },
			};
#if WITH_METADATA
			const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/MazeGenerator.h" },
				{ "PATH.DisplayName", "PATH" },
				{ "PATH.Name", "MazeTileType::PATH" },
				{ "WALL.DisplayName", "WALL" },
				{ "WALL.Name", "MazeTileType::WALL" },
			};
#endif
			static const UECodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_RaiderOfTimeProto,
				nullptr,
				"MazeTileType",
				"MazeTileType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UECodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UECodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* MazePathDirection_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_RaiderOfTimeProto_MazePathDirection, Z_Construct_UPackage__Script_RaiderOfTimeProto(), TEXT("MazePathDirection"));
		}
		return Singleton;
	}
	template<> RAIDEROFTIMEPROTO_API UEnum* StaticEnum<MazePathDirection>()
	{
		return MazePathDirection_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_MazePathDirection(MazePathDirection_StaticEnum, TEXT("/Script/RaiderOfTimeProto"), TEXT("MazePathDirection"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_RaiderOfTimeProto_MazePathDirection_Hash() { return 2300317439U; }
	UEnum* Z_Construct_UEnum_RaiderOfTimeProto_MazePathDirection()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_RaiderOfTimeProto();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("MazePathDirection"), 0, Get_Z_Construct_UEnum_RaiderOfTimeProto_MazePathDirection_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UECodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "MazePathDirection::DOWN", (int64)MazePathDirection::DOWN },
				{ "MazePathDirection::LEFT", (int64)MazePathDirection::LEFT },
				{ "MazePathDirection::UP", (int64)MazePathDirection::UP },
				{ "MazePathDirection::RIGHT", (int64)MazePathDirection::RIGHT },
			};
#if WITH_METADATA
			const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "DOWN.DisplayName", "DOWN" },
				{ "DOWN.Name", "MazePathDirection::DOWN" },
				{ "LEFT.DisplayName", "LEFT" },
				{ "LEFT.Name", "MazePathDirection::LEFT" },
				{ "ModuleRelativePath", "Public/MazeGenerator.h" },
				{ "RIGHT.DisplayName", "RIGHT" },
				{ "RIGHT.Name", "MazePathDirection::RIGHT" },
				{ "UP.DisplayName", "UP" },
				{ "UP.Name", "MazePathDirection::UP" },
			};
#endif
			static const UECodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_RaiderOfTimeProto,
				nullptr,
				"MazePathDirection",
				"MazePathDirection",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UECodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UECodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FMazeGeneratorData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern RAIDEROFTIMEPROTO_API uint32 Get_Z_Construct_UScriptStruct_FMazeGeneratorData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FMazeGeneratorData, Z_Construct_UPackage__Script_RaiderOfTimeProto(), TEXT("MazeGeneratorData"), sizeof(FMazeGeneratorData), Get_Z_Construct_UScriptStruct_FMazeGeneratorData_Hash());
	}
	return Singleton;
}
template<> RAIDEROFTIMEPROTO_API UScriptStruct* StaticStruct<FMazeGeneratorData>()
{
	return FMazeGeneratorData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FMazeGeneratorData(FMazeGeneratorData::StaticStruct, TEXT("/Script/RaiderOfTimeProto"), TEXT("MazeGeneratorData"), false, nullptr, nullptr);
static struct FScriptStruct_RaiderOfTimeProto_StaticRegisterNativesFMazeGeneratorData
{
	FScriptStruct_RaiderOfTimeProto_StaticRegisterNativesFMazeGeneratorData()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("MazeGeneratorData")),new UScriptStruct::TCppStructOps<FMazeGeneratorData>);
	}
} ScriptStruct_RaiderOfTimeProto_StaticRegisterNativesFMazeGeneratorData;
	struct Z_Construct_UScriptStruct_FMazeGeneratorData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_width_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_width;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_height_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_height;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/MazeGenerator.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMazeGeneratorData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_width_MetaData[] = {
		{ "Category", "MazeGenerator" },
		{ "ModuleRelativePath", "Public/MazeGenerator.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_width = { "width", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMazeGeneratorData, width), METADATA_PARAMS(Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_width_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_width_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_height_MetaData[] = {
		{ "Category", "MazeGenerator" },
		{ "ModuleRelativePath", "Public/MazeGenerator.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_height = { "height", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMazeGeneratorData, height), METADATA_PARAMS(Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_height_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_height_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_width,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::NewProp_height,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RaiderOfTimeProto,
		nullptr,
		&NewStructOps,
		"MazeGeneratorData",
		sizeof(FMazeGeneratorData),
		alignof(FMazeGeneratorData),
		Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FMazeGeneratorData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FMazeGeneratorData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_RaiderOfTimeProto();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("MazeGeneratorData"), sizeof(FMazeGeneratorData), Get_Z_Construct_UScriptStruct_FMazeGeneratorData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UECodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FMazeGeneratorData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FMazeGeneratorData_Hash() { return 2503166918U; }
class UScriptStruct* FTileArray::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern RAIDEROFTIMEPROTO_API uint32 Get_Z_Construct_UScriptStruct_FTileArray_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FTileArray, Z_Construct_UPackage__Script_RaiderOfTimeProto(), TEXT("TileArray"), sizeof(FTileArray), Get_Z_Construct_UScriptStruct_FTileArray_Hash());
	}
	return Singleton;
}
template<> RAIDEROFTIMEPROTO_API UScriptStruct* StaticStruct<FTileArray>()
{
	return FTileArray::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FTileArray(FTileArray::StaticStruct, TEXT("/Script/RaiderOfTimeProto"), TEXT("TileArray"), false, nullptr, nullptr);
static struct FScriptStruct_RaiderOfTimeProto_StaticRegisterNativesFTileArray
{
	FScriptStruct_RaiderOfTimeProto_StaticRegisterNativesFTileArray()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("TileArray")),new UScriptStruct::TCppStructOps<FTileArray>);
	}
} ScriptStruct_RaiderOfTimeProto_StaticRegisterNativesFTileArray;
	struct Z_Construct_UScriptStruct_FTileArray_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FBytePropertyParams NewProp_tiles_Inner_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_tiles_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_tiles_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_tiles;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTileArray_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/MazeGenerator.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTileArray_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTileArray>();
	}
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles_Inner_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles_Inner = { "tiles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UEnum_RaiderOfTimeProto_MazeTileType, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles_MetaData[] = {
		{ "Category", "MazeGenerator" },
		{ "ModuleRelativePath", "Public/MazeGenerator.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles = { "tiles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTileArray, tiles), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTileArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles_Inner_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTileArray_Statics::NewProp_tiles,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTileArray_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RaiderOfTimeProto,
		nullptr,
		&NewStructOps,
		"TileArray",
		sizeof(FTileArray),
		alignof(FTileArray),
		Z_Construct_UScriptStruct_FTileArray_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTileArray_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FTileArray_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTileArray_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTileArray()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FTileArray_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_RaiderOfTimeProto();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("TileArray"), sizeof(FTileArray), Get_Z_Construct_UScriptStruct_FTileArray_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UECodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FTileArray_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FTileArray_Hash() { return 409165601U; }
	DEFINE_FUNCTION(UMazeGenerator::execGenerateMaze)
	{
		P_GET_STRUCT_REF(FMazeGeneratorData,Z_Param_Out_data);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FTileArray>*)Z_Param__Result=UMazeGenerator::GenerateMaze(Z_Param_Out_data);
		P_NATIVE_END;
	}
	void UMazeGenerator::StaticRegisterNativesUMazeGenerator()
	{
		UClass* Class = UMazeGenerator::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GenerateMaze", &UMazeGenerator::execGenerateMaze },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics
	{
		struct MazeGenerator_eventGenerateMaze_Parms
		{
			FMazeGeneratorData data;
			TArray<FTileArray> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_data_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_data;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_data = { "data", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MazeGenerator_eventGenerateMaze_Parms, data), Z_Construct_UScriptStruct_FMazeGeneratorData, METADATA_PARAMS(Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_data_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_data_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FTileArray, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MazeGenerator_eventGenerateMaze_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_data,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::Function_MetaDataParams[] = {
		{ "Category", "MazeGenerator" },
		{ "ModuleRelativePath", "Public/MazeGenerator.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMazeGenerator, nullptr, "GenerateMaze", nullptr, nullptr, sizeof(MazeGenerator_eventGenerateMaze_Parms), Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMazeGenerator_GenerateMaze()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMazeGenerator_GenerateMaze_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UMazeGenerator_NoRegister()
	{
		return UMazeGenerator::StaticClass();
	}
	struct Z_Construct_UClass_UMazeGenerator_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMazeGenerator_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_RaiderOfTimeProto,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UMazeGenerator_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UMazeGenerator_GenerateMaze, "GenerateMaze" }, // 1223785936
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMazeGenerator_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "MazeGenerator.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/MazeGenerator.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMazeGenerator_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMazeGenerator>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMazeGenerator_Statics::ClassParams = {
		&UMazeGenerator::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UMazeGenerator_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMazeGenerator_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMazeGenerator()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMazeGenerator_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UMazeGenerator, 1068954863);
	template<> RAIDEROFTIMEPROTO_API UClass* StaticClass<UMazeGenerator>()
	{
		return UMazeGenerator::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMazeGenerator(Z_Construct_UClass_UMazeGenerator, &UMazeGenerator::StaticClass, TEXT("/Script/RaiderOfTimeProto"), TEXT("UMazeGenerator"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMazeGenerator);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
