// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolbarPluginCommands.h"

#define LOCTEXT_NAMESPACE "FToolbarPluginModule"

void FToolbarPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ToolbarPlugin", "Execute ToolbarPlugin action", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(PluginAction2, "ToolbarPlugin2", "Execute ToolbarPlugin action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
