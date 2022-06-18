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
		FGameplayTag skill_Tag;			// 어떤 스킬인지 스킬태그

	class ABaseCharacter* owner;		// owner

	// 스폰할 Actor 설정
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorToSpawn;	// 스폰할 ActorBP
	UPROPERTY(EditAnywhere)
		FRotator spawnRotation;					// 스폰할 회전값
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;					// 스폰할 위치 : 소켓
	UPROPERTY(EditAnywhere)
		float projectileSpeed;					// projectileActor 속도
	UPROPERTY(EditAnywhere)
		int32 spawnCount = 1;					// 스폰 개수
	UPROPERTY(VisibleAnywhere)
		class AProjectileActor* projectileActor;	// 소환된 projectileActor

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
	// 발사할 방향 구하는 함수
	//FVector GetShotDir(class ABaseCharacter* characterOwner);
};
