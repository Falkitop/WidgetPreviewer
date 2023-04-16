#pragma once
#include "EditorUtilityWidgetBlueprint.h"
 	

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "UMGPreviewSettings.generated.h"



UCLASS(config=Editor)
class UUMGPreviewSettings : public UObject
{
	GENERATED_BODY()
public:

	static void RegisterSettings()
	{
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

		if (SettingsModule != nullptr)
		{
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "WidgetPreview",
				FText::FromString("UMGPreview"),
				FText::FromString("UMGPreview for previewing Widgets in the editor"),
				GetMutableDefault<UUMGPreviewSettings>()
				);

			if (SettingsSection.IsValid())
			{
				SettingsSection->OnModified().BindLambda([]() -> bool
				{
					 GetMutableDefault<UUMGPreviewSettings>()->SaveConfig();
					return true;
					//return UWidgetPreviewSettings::HandleSettingsSaved();
					//UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
				});
			}
		}
	}
	
	bool HandleSettingsSaved()
	{
		SaveConfig();
		return true;
		//FUMGPreviewModule::DefaultWidget = 
	}
	
	/** GameMode to use if not specified in any other way. (e.g. per-map DefaultGameMode or on the URL). */
	UPROPERTY(config, noclear, EditAnywhere, meta=(MetaClass="EditorUtilityWidgetBlueprint"))
	TSoftObjectPtr<UEditorUtilityWidgetBlueprint> DefaultEditorWidget;
};



