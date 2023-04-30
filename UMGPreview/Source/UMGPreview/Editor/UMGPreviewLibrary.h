#pragma once
#include "UMGPreviewSettings.h"
#include "Blueprint/UserWidget.h"
#include "UMGPreviewLibrary.generated.h"

UCLASS(Blueprintable)
class UMGPREVIEW_API UUMGPreviewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintPure)
	static UTexture2D* GetPreviewBackground(UUserWidget* Widget)
	{
		//return (Widget->PreviewBackground == nullptr) ? nullptr : Widget->PreviewBackground;
		return nullptr;
	}
	
	UFUNCTION(BlueprintCallable)
	static bool IsDefaultEditorWidgetValid()
	{
		
		return GetDefault<UUMGPreviewSettings>()->DefaultEditorWidget.Get() != nullptr;;
	}
	
};