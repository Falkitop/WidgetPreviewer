// Copyright Epic Games, Inc. All Rights Reserved.

#include "UMGPreview.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "Editor/UMGPreviewSettings.h"
#include "Editor/WidgetPreviewExtension.h"

#define LOCTEXT_NAMESPACE "FUMGPreviewModule"



void FUMGPreviewModule::StartupModule()
{

	//Install Content Browser Hook
	FWidgetPreviewExtension::InstallHook();
	
	// Register ProjectSettings
	UUMGPreviewSettings::RegisterSettings();
	
}

void FUMGPreviewModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUMGPreviewModule, UMGPreview)