// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindow.h"
#include "StandaloneWindowStyle.h"
#include "StandaloneWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName StandaloneWindowTabName("StandaloneWindow");

#define LOCTEXT_NAMESPACE "FStandaloneWindowModule"

void FStandaloneWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FStandaloneWindowStyle::Initialize();
	FStandaloneWindowStyle::ReloadTextures();

	FStandaloneWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneWindowModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStandaloneWindowModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWindowTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneWindowTabTitle", "StandaloneWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FStandaloneWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStandaloneWindowStyle::Shutdown();

	FStandaloneWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneWindowTabName);
}

TSharedRef<SDockTab> FStandaloneWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FStandaloneWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("StandaloneWindow.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FStandaloneWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(StandaloneWindowTabName);
}

void FStandaloneWindowModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStandaloneWindowCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStandaloneWindowCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneWindowModule, StandaloneWindow)