// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

void AMainGameMode::ShowLoadingScreen(TSubclassOf<UUserWidget> UserWidgetClass) {
	UUserWidget* LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
	LoadingWidget->AddToViewport();
}