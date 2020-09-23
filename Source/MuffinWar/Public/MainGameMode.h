// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
class UUserWidget;
class UBaseMenu;

UCLASS()
class MUFFINWAR_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UBaseMenu* MenuWidget;
	UUserWidget* LoadingWidget;

	enum class UIControl;

	void ShowLoadingScreen();
	void ChangeUIControl(UIControl ControlType);
	void SetInputMode(EMouseLockMode LockMode, bool bShowMouse);
protected: 
	UFUNCTION(BlueprintCallable)
	void InitializeWidgets(TSubclassOf<UUserWidget> MenuWidgetClass, TSubclassOf<UUserWidget> LoadingWidgetClass);

	UFUNCTION(BlueprintCallable)
	void ShowMainMenu();
public:
	void LoadGame();
};
