// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedFinalProjectGameMode.h"
#include "AdvancedFinalProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAdvancedFinalProjectGameMode::AAdvancedFinalProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
