// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMenu.h"
#include "MainGameMode.h"

void UBaseMenu::RegisterOnStartCallback(AMainGameMode* GameMode) {
	MainGameMode = GameMode;
}

void UBaseMenu::OnClickStart() {
	if (MainGameMode) {
		MainGameMode->LoadGame();
	}
}

