// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_SpawnActor.generated.h"


// 스폰할 타깃
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
		TSubclassOf<AActor> actorToSpawn;			// 스폰할 ActorBP
	UPROPERTY(EditAnywhere)
		ETarget spawnTarget = ETarget::TARGET;		// 스폰할 위치 타겟
	FVector spawnLocation;							// 스폰 Location
	FRotator spawnRotator = FRotator::ZeroRotator;	// 스폰 Rotator

	float rayLength = 200.f;			// 밑으로 레이 쏠 길이


	UPROPERTY(EditAnywhere)
		bool isSkillAttack = false;		// 스킬 공격인지?
	UPROPERTY(EditAnywhere, meta = (EditCondition = "isSkillAttack == true"))
		FGameplayTag skill_Tag;			// 스킬 태그
public:
	void SetSpawnLocation();
};

