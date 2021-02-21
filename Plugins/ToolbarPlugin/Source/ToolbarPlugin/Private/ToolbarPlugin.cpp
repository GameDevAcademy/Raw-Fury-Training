// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolbarPlugin.h"
#include "ToolbarPluginStyle.h"
#include "ToolbarPluginCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName ToolbarPluginTabName("ToolbarPlugin");

#define LOCTEXT_NAMESPACE "FToolbarPluginModule"

void FToolbarPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FToolbarPluginStyle::Initialize();
	FToolbarPluginStyle::ReloadTextures();

	FToolbarPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FToolbarPluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FToolbarPluginModule::PluginButtonClicked),
		FCanExecuteAction());

    PluginCommands2 = MakeShareable(new FUICommandList);

    PluginCommands2->MapAction(
        FToolbarPluginCommands::Get().PluginAction2,
        FExecuteAction::CreateRaw(this, &FToolbarPluginModule::PluginButtonClicked2),
        FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FToolbarPluginModule::RegisterMenus));
}

void FToolbarPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FToolbarPluginStyle::Shutdown();

	FToolbarPluginCommands::Unregister();
}

void FToolbarPluginModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = LOCTEXT("PluginButtonDialogText", "blah");
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FToolbarPluginModule::PluginButtonClicked2()
{
    // Put your "OnButtonClicked" stuff here
    FText DialogText = LOCTEXT("PluginButtonDialogText2", "blah2");
    FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FToolbarPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FToolbarPluginCommands::Get().PluginAction, PluginCommands);
            Section.AddMenuEntryWithCommandList(FToolbarPluginCommands::Get().PluginAction2, PluginCommands2);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FToolbarPluginCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);

                FToolMenuEntry& Entry2 = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FToolbarPluginCommands::Get().PluginAction2));
                Entry2.SetCommandList(PluginCommands2);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToolbarPluginModule, ToolbarPlugin)