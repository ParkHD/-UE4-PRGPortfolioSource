// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_ShootProjectileActor.generated.h"

// ProjectileActor Spawn NotifyState
// 프로젝타일 액터를 스폰하고 일정 시간 후에 발사한다.
UCLASS()
class UE4_UNDERWORLD_API UNotifyState_ShootProjectileActor : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(EditAnywhere)
		bool isSkill = false;			// 스킬 사용인지
	UPROPERTY(EditAnywhere, meta = (EditCondition = "isSkill == true"))
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

	UPROPERTY(VisibleAnywhere)
		class AProjectileActor* projectileActor;	// 소환된 projectileActor

	FVector projectileDir;						// 방향
public:
	// 발사할 방향 구하는 함수
	FVector GetShotDir(class ABaseCharacter* characterOwner);
};
