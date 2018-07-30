// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UltimateFrisballGameMode.h"
#include "UltimateFrisballPawn.h"
#include "UltimateFrisballHud.h"

AUltimateFrisballGameMode::AUltimateFrisballGameMode()
{
	DefaultPawnClass = AUltimateFrisballPawn::StaticClass();
	HUDClass = AUltimateFrisballHud::StaticClass();
}
