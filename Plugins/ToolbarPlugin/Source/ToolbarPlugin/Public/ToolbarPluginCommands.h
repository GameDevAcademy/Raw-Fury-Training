// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ToolbarPluginStyle.h"

class FToolbarPluginCommands : public TCommands<FToolbarPluginCommands>
{
public:

	FToolbarPluginCommands()
		: TCommands<FToolbarPluginCommands>(TEXT("ToolbarPlugin"), NSLOCTEXT("Contexts", "ToolbarPlugin", "ToolbarPlugin Plugin"), NAME_None, FToolbarPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
