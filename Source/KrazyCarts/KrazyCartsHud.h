// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "KrazyCartsHud.generated.h"


UCLASS(config = Game)
class AKrazyCartsHud : public AHUD
{
	GENERATED_BODY()

public:
	AKrazyCartsHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
