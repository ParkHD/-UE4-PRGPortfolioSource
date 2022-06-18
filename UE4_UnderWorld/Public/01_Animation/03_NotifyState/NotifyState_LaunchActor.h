// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "NotifyState_LaunchActor.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UNotifyState_LaunchActor : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;			// � ��ų���� ��ų�±�

	class ABaseCharacter* owner;		// owner

	// ������ Actor ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorToSpawn;	// ������ ActorBP
	UPROPERTY(EditAnywhere)
		FRotator spawnRotation;					// ������ ȸ����
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;					// ������ ��ġ : ����
	UPROPERTY(EditAnywhere)
		float projectileSpeed;					// projectileActor �ӵ�
	UPROPERTY(EditAnywhere)
		int32 spawnCount = 1;					// ���� ����
	UPROPERTY(VisibleAnywhere)
		class AProjectileActor* projectileActor;	// ��ȯ�� projectileActor

	UPROPERTY(EditAnywhere)
		float upDistance;
	UPROPERTY(EditAnywhere)
		float fowardDistance = 100.f;
	UPROPERTY(EditAnywhere)
		float radius = 100.f;
	TArray<float> spawnTime;
		UPROPERTY(VisibleAnywhere)
	TArray<FVector> targetLocation;
	int index = 0;
	float time = 0;
public:
	// �߻��� ���� ���ϴ� �Լ�
	//FVector GetShotDir(class ABaseCharacter* characterOwner);
};
