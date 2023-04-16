#pragma once
#include "AssetTypeActions_Base.h"
#include "WidgetBlueprint.h"

class FWidgetPreviewExtension
{
public:

	static UWidgetBlueprint SelectedWidgetBlueprint;
	static void InstallHook();
	static void RemoveHook();
	static void ExecuteRun();
};
