// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Component/00_Character/QuickSlotComponent.h"

// Sets default values for this component's properties
UQuickSlotComponent::UQuickSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	quickSlotList.Init(nullptr, 16);
	// ...
}


// Called when the game starts
void UQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuickSlotComponent::SwapQuickSlot(int firstIndex, int secondIndex)
{
	quickSlotList.Swap(firstIndex, secondIndex);
	OnUpdateQuickSlot.Broadcast(quickSlotList);
}

void UQuickSlotComponent::UpdateQuickSlot()
{
	OnUpdateQuickSlot.Broadcast(quickSlotList);
}
