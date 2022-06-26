// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuickSlotComponent.generated.h"

// ������ ������Ʈ�� ���� ��������Ʈ �Լ�
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
		class APlayerCharacter* owner;		// ������Ʈ ������
public:
	UPROPERTY(VisibleAnywhere)
		TArray<UObject*> quickSlotList;		// �� ���� �迭
public:
	// �־��� �ε��� ���� ��ġ�� ����
	void SwapQuickSlot(int firstIndex, int secondIndex);
	// ������ ���� ������Ʈ
	void UpdateQuickSlot();
public:
	// ������ ��� ���� �Լ�
	void PressQuickSlot(int index);
	void ReleaseQuickSlot(int index);
public:
	// ������ ������Ʈ ��������Ʈ
	FOnUpdateQuickSlot OnUpdateQuickSlot;
};

