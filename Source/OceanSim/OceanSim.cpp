// Copyright Epic Games, Inc. All Rights Reserved.

#include "OceanSim.h"
#include "Modules/ModuleManager.h"

void FShadersModule::StartupModule()
{
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
}

void FShadersModule::ShutdownModule()
{
}

IMPLEMENT_PRIMARY_GAME_MODULE( FShadersModule, OceanSim, "OceanSim" );