// Copyright Epic Games, Inc. All Rights Reserved.

#include "KrazyCartsGameMode.h"
#include "KrazyCartsPawn.h"
#include "KrazyCartsHud.h"

AKrazyCartsGameMode::AKrazyCartsGameMode()
{
	DefaultPawnClass = AKrazyCartsPawn::StaticClass();
	HUDClass = AKrazyCartsHud::StaticClass();
}
