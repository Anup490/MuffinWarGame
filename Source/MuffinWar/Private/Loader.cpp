// Fill out your copyright notice in the Description page of Project Settings.
#include "Loader.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"

struct FLoadingScreenBrush : public FSlateDynamicImageBrush {
	FLoadingScreenBrush(FName TextureName, FVector2D Size) : FSlateDynamicImageBrush(TextureName, Size) {
		SetResourceObject(LoadObject<UObject>(NULL, *TextureName.ToString()));
	}
};

class SLoadingScreen : public SCompoundWidget {
	FSlateDynamicImageBrush* LoadingBrush;
public:
	SLATE_BEGIN_ARGS(SLoadingScreen) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& Args) {
		static FName LoadingScreenName(TEXT("/Game/ThirdPersonCPP/UI/Loading"));
		LoadingBrush = new FLoadingScreenBrush(LoadingScreenName, FVector2D(1024, 256));
		ChildSlot
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(LoadingBrush)
				]
			];
	}
};

ULoader::ULoader() {}

void ULoader::ShowLoadingScreen() {
	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreen.bWaitForManualStop = true;
	LoadingScreen.bAllowEngineTick = true;
	LoadingScreen.MinimumLoadingScreenDisplayTime = 1000.f;
	LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen);
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	UE_LOG(LogTemp, Warning, TEXT("isMoviePlayerEnabled :: %d"), IsMoviePlayerEnabled())


	


}