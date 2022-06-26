// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuickSlotComponent.generated.h"

// 퀵슬롯 업데이트를 위한 델리게이트 함수
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateQuickSlot, TArray<class UObject*>, QuickArray);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_UNDERWORLD_API UQuickSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuickSlotComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
		class APlayerCharacter* owner;		// 컴포넌트 소유자
public:
	UPROPERTY(VisibleAnywhere)
		TArray<UObject*> quickSlotList;		// 퀵 슬롯 배열
public:
	// 주어진 인덱스 끼리 위치를 스왑
	void SwapQuickSlot(int firstIndex, int secondIndex);
	// 퀵슬롯 위젯 업데이트
	void UpdateQuickSlot();
public:
	// 퀵슬롯 사용 관련 함수
	void PressQuickSlot(int index);
	void ReleaseQuickSlot(int index);
public:
	// 퀵슬롯 업데이트 델리게이트
	FOnUpdateQuickSlot OnUpdateQuickSlot;
};

