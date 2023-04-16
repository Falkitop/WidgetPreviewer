// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "Modules/ModuleManager.h"



class FUMGPreviewModule : public IModuleInterface
{
public:
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
