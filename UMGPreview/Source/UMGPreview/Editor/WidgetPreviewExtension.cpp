#include "WidgetPreviewExtension.h"

#include "BlueprintEditorModule.h"
#include "ContentBrowserDelegates.h"
#include "ContentBrowserModule.h"
#include "EngineUtils.h"
#include "ToolMenu.h"
#include "ToolMenuSection.h"
#include "WidgetBlueprint.h"
#include "UMGPreview/UMGPreview.h"
#include "UMGPreviewSettings.h"



static FContentBrowserMenuExtender_SelectedAssets ContentBrowserExtenderDelegate;
static FDelegateHandle ContentBrowserExtenderDelegateHandle;





//Extension for ContentBrowser ContextMenu
class FWidgetPreviewContentBrowserExtention_Impl
{
public:
	static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets)
	{
		TSharedRef<FExtender> Extender(new FExtender());
		if(SelectedAssets[0].GetClass() != UWidgetBlueprint::StaticClass() && SelectedAssets.Num() > 0)
			return Extender;
		Extender->AddMenuExtension(
		"CommonAssetActions",
		EExtensionHook::First,
		nullptr,
		FMenuExtensionDelegate::CreateStatic(&OpenMenu)
		);
		return  Extender;
	}
	
	static void OpenMenu(FMenuBuilder& MenuBuilder)
	{
		MenuBuilder.AddMenuEntry(
		FText::FromString("Preview Widget"),
		FText::FromString("Tooltip"),
		FSlateIcon("EditorStyle", "GraphEditor.Event_16x"),
		FUIAction(FExecuteAction::CreateLambda([]
		{
			UE_LOG(LogEngine, Error, TEXT("WidgetPreviewWindow"));
			FWidgetPreviewExtension::ExecuteRun();
		}))
		);
		
	}

	static TArray<FContentBrowserMenuExtender_SelectedAssets>& GetExtenderDelegates()
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
		return ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
	}
};


void FWidgetPreviewExtension::InstallHook()
{
	ContentBrowserExtenderDelegate = FContentBrowserMenuExtender_SelectedAssets::CreateStatic(&FWidgetPreviewContentBrowserExtention_Impl::OnExtendContentBrowserAssetSelectionMenu);
	TArray<FContentBrowserMenuExtender_SelectedAssets>& CBMenuExtenderDelegates = FWidgetPreviewContentBrowserExtention_Impl::GetExtenderDelegates();
	CBMenuExtenderDelegates.Add(ContentBrowserExtenderDelegate);
	ContentBrowserExtenderDelegateHandle = CBMenuExtenderDelegates.Last().GetHandle();
}

void FWidgetPreviewExtension::RemoveHook()
{
}

void FWidgetPreviewExtension::ExecuteRun()
{
	const UUMGPreviewSettings* Settings = GetDefault<UUMGPreviewSettings>();
	UEditorUtilityWidgetBlueprint* EditorWidget = LoadObject<UEditorUtilityWidgetBlueprint>(NULL,TEXT("/UMGPreview/UMGPreview.UMGPreview"), NULL); //Settings->DefaultEditorWidget.Get();
	if (EditorWidget)
	{
		//UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		//EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);

		auto MyWindow = SNew(SWindow)
		.ClientSize(FVector2D(640, 480));
		FSlateApplication::Get().AddWindow(MyWindow, true);

		
		SOverlay::FOverlaySlot& Overlay = MyWindow->AddOverlaySlot();
		Overlay.Padding(40);
		
		Overlay.AttachWidget(EditorWidget->CreateUtilityWidget());
		
		
	}
}
