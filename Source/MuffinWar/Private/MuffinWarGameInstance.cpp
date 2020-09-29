// Fill out your copyright notice in the Description page of Project Settings.


#include "MuffinWarGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMuffinWarGameInstance::LoadMenu() {}

void UMuffinWarGameInstance::LoadGame() 
{
	UGameplayStatics::OpenLevel(GetWorld(),FName("Game"),true, FString());
}