// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MuffinWarGameMode.generated.h"

UCLASS(minimalapi)
class AMuffinWarGameMode : public AGameModeBase
{
	GENERATED_BODY()

	bool bIsGamePaused;
	class UUserWidget* PauseMenuWidget;
	class UUserWidget* LoadScreenWidget;
	class AMuffinWarCharacter* MuffinWarCharacter;
protected:
	UFUNCTION(BlueprintCallable)
	void InitializeWidgets(TSubclassOf<class UUserWidget> PauseMenuWidgetClass
		, TSubclassOf<class UUserWidget> LoadingScreenWidgetClass);
public:
	AMuffinWarGameMode();
	void PauseGame(class AMuffinWarCharacter* Player);
	bool IsGamePaused();

	UFUNCTION(BlueprintCallable)
	void UnpauseGame();

	UFUNCTION(BlueprintCallable)
	void QuitGame();
};



