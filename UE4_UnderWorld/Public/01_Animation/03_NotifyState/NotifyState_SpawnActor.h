// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_SpawnActor.generated.h"


// ������ Ÿ��
UENUM(BlueprintType)
enum class ETarget : uint8
{
	ME,
	TARGET,
};
UCLASS()
class UE4_UNDERWORLD_API UNotifyState_SpawnActor : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	UPROPERTY()
		class ABaseCharacter* owner;				// owner

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> actorToSpawn;			// ������ ActorBP
	UPROPERTY(EditAnywhere)
		ETarget spawnTarget = ETarget::TARGET;		// ������ ��ġ Ÿ��
	FVector spawnLocation;							// ���� Location
	FRotator spawnRotator = FRotator::ZeroRotator;	// ���� Rotator

	float rayLength = 200.f;			// ������ ���� �� ����


	UPROPERTY(EditAnywhere)
		bool isSkillAttack = false;		// ��ų ��������?
	UPROPERTY(EditAnywhere, meta = (EditCondition = "isSkillAttack == true"))
		FGameplayTag skill_Tag;			// ��ų �±�
public:
	void SetSpawnLocation();
};

