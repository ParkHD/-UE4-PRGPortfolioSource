// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_FootStep.generated.h"

// ���ڱ����� Asset ����ü
USTRUCT(BlueprintType)
struct FFootStep
{
	GENERATED_BODY()
public:
	// �Ϲ� ����
	UPROPERTY(EditAnywhere)
		class UParticleSystem* GroundFootParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* GroundFootSound;

	// �� ����
	UPROPERTY(EditAnywhere)
		class UParticleSystem* SnowFootParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* SnowFootSound;

	// �� ����
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
		bool bAttenuation = true;		// �Ҹ��� ������ �ִ��� ����
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bAttenuation == true"))
		float falloffDistance = 4000.f;	// �Ҹ� ��ȿ ���� ����

	UPROPERTY(EditAnywhere)
		FName footSocketName;	// ���ڱ� ���� ��ġ
	UPROPERTY(EditAnywhere)
		FFootStep footStep;		// ���ڱ� �� ���� Asset
	UPROPERTY(EditAnywhere)
		float rayLength;		// �� �Ʒ� ���� Ÿ���� �˻��� Ray����
};
