// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MuffinWarGameMode.generated.h"

UCLASS(minimalapi)
class AMuffinWarGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsGamePaused;
public:
	AMuffinWarGameMode();
	void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	bool IsGamePaused();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PauseGame();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnPlayerDeath();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UnpauseGame();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void QuitGame();
};



