// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_FootStep.generated.h"

// 발자국관련 Asset 구조체
USTRUCT(BlueprintType)
struct FFootStep
{
	GENERATED_BODY()
public:
	// 일반 지형
	UPROPERTY(EditAnywhere)
		class UParticleSystem* GroundFootParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* GroundFootSound;

	// 눈 지형
	UPROPERTY(EditAnywhere)
		class UParticleSystem* SnowFootParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* SnowFootSound;

	// 물 지형
	UPROPERTY(EditAnywhere)
		class UParticleSystem* WaterFootParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* WaterFootSound;
};
UCLASS()
class UE4_UNDERWORLD_API UNotify_FootStep : public UAnimNotify
{
	GENERATED_BODY()
public:
	UNotify_FootStep();
protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	UPROPERTY(EditAnywhere)
		bool bAttenuation = true;		// 소리가 범위가 있는지 설정
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bAttenuation == true"))
		float falloffDistance = 4000.f;	// 소리 유효 범위 설정

	UPROPERTY(EditAnywhere)
		FName footSocketName;	// 발자국 생성 위치
	UPROPERTY(EditAnywhere)
		FFootStep footStep;		// 발자국 및 사운드 Asset
	UPROPERTY(EditAnywhere)
		float rayLength;		// 발 아래 땅의 타입을 검사할 Ray길이
};
