// Copyright Epic Games, Inc. All Rights Reserved.

#include "OceanSimGameMode.h"
#include "OceanSimCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOceanSimGameMode::AOceanSimGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
