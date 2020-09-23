// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"
#include "BaseMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MuffinWarGameInstance.h"

void AMainGameMode::InitializeWidgets(TSubclassOf<UUserWidget> MenuWidgetClass, TSubclassOf<UUserWidget> LoadingWidgetClass) {
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	MenuWidget = Cast<UBaseMenu>(Widget);
	LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetClass);
}

void AMainGameMode::ShowMainMenu() {
	if (MenuWidget) {
		MenuWidget->RegisterOnStartCallback(this);
		MenuWidget->AddToViewport();
		ShowMouseCursor(true);
	}
}

void AMainGameMode::ShowLoadingScreen() {
	if (MenuWidget) {
		MenuWidget->RemoveFromViewport();
	}
	if (LoadingWidget) {
		ShowMouseCursor(false);
		LoadingWidget->AddToViewport();
	}
}

void AMainGameMode::LoadGame() {
	ShowLoadingScreen();
	UMuffinWarGameInstance* MuffinWarGame = Cast<UMuffinWarGameInstance>(GetGameInstance());
	if (MuffinWarGame) {
		MuffinWarGame->LoadGame();
	}
}

void AMainGameMode::ShowMouseCursor(bool bShowMouse) {
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->bShowMouseCursor = bShowMouse;
}