// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "GameFramework/Actor.h"
#include "SkillRangeActor.generated.h"

UCLASS()
class UE4_UNDERWORLD_API ASkillRangeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillRangeActor();

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = CapsuleComponent)
		class UCapsuleComponent* CapsuleComponent;							// 공격 범위 콜리전
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = DecalComponent)
		class UDecalComponent* DecalComponent;								// 공격 범위 데칼
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Sound)
		class UAudioComponent* audioComponent;								// 스킬 사운드
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Particle)
		class UParticleSystemComponent* SkillParticleComponent;				// 스킬 파티클

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
		float attackDelay = 3.f;			// 스폰 후 공격 시작 딜레이
	UPROPERTY(EditAnywhere)
		float cameraShakeScale = 1.f;		// 카메라 쉐이크 스케일
	UPROPERTY(EditAnywhere)
		TArray<class AActor*> hitActors;	// 피격 대상

	UPROPERTY(EditAnywhere)
		EAttackType attackType = EAttackType::NORMAL;
	float damageAmount = 0.f;	// 대미지
	float damageValue = 0.f;	// 대미지 Value(스턴 타임, 넉백 파워) 
protected:
	void AttackRange();
public:
	void SetDamage(float damage);
	void SetValue(float value);
protected:
	UFUNCTION()
		void OnActorOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
};

inline void ASkillRangeActor::SetValue(float value)
{
	damageValue = value;
}
