// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"
#include "BaseMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

enum class AMainGameMode::UIControl {
	ENABLE, DISABLE
};

void AMainGameMode::InitializeWidgets(TSubclassOf<UUserWidget> MenuWidgetClass, TSubclassOf<UUserWidget> LoadingWidgetClass) {
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	MenuWidget = Cast<UBaseMenu>(Widget);
	LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetClass);
}

void AMainGameMode::ShowMainMenu() {
	if (MenuWidget) {
		MenuWidget->RegisterOnStartCallback(this);
		MenuWidget->AddToViewport();
		ChangeUIControl(UIControl::ENABLE);
	}
}

void AMainGameMode::ShowLoadingScreen() {
	if (MenuWidget) {
		MenuWidget->RemoveFromViewport();
	}
	if (LoadingWidget) {
		ChangeUIControl(UIControl::DISABLE);
		LoadingWidget->AddToViewport();
	}
}

void AMainGameMode::LoadGame() {
	ShowLoadingScreen();
}

void AMainGameMode::ChangeUIControl(UIControl ControlType) {
	switch (ControlType) {
	case UIControl::ENABLE:
		SetInputMode(EMouseLockMode::LockAlways, true);
		break;
	case UIControl::DISABLE:
		SetInputMode(EMouseLockMode::DoNotLock, false);
		break;
	}
}

void AMainGameMode::SetInputMode(EMouseLockMode LockMode, bool bShowMouse) {
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(LockMode);
	UGameplayStatics::GetPlayerController(this, 0);
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = bShowMouse;
}