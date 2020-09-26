// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseLocationService.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

#define BLACKBOARD_KEY "Destination"

void UBaseLocationService::OnActivate(APawn* Pawn) 
{
	FVector Destination = UNavigationSystemV1::GetRandomPointInNavigableRadius(
		Pawn->GetWorld(),
		Pawn->GetActorLocation(),
		fNavigableRadius,
		nullptr,
		nullptr
	);
	UAIBlueprintHelperLibrary::GetBlackboard(Pawn)->SetValueAsVector(BLACKBOARD_KEY, Destination);
}