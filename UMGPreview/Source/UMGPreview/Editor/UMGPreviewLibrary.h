#pragma once
#include "Blueprint/UserWidget.h"
#include "UMGPreviewLibrary.generated.h"

UCLASS()
class UMGPREVIEW_API UUMGPreviewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintPure)
	static UTexture2D* GetPreviewBackground(UUserWidget* Widget)
	{
		//return (Widget->PreviewBackground == nullptr) ? nullptr : Widget->PreviewBackground;
		return nullptr;
	}
	
};