// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class UE4_UNDERWORLD_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* sphereComponent;					// 공격 반응을 할 콜리전
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* skeletalMeshComponent;		// 물체 모습
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* projectileComponent;	
	UPROPERTY(EditAnywhere)
		class UAudioComponent* audioComponent;						// 사운드
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UNiagaraComponent* niagaraSys;						// Niagara 효과
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* particleComponent;			// 효과
public:
	class UProjectileMovementComponent* GetProjectileComponent() { return projectileComponent; }

protected:
	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;			// overlap반응 시 터지는 효과
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* hitParticle_Nia;		// overlap반응 시 터지는 효과_Niagara
	UPROPERTY(EditAnywhere)
		class USoundBase* soundToPlay;				// overlap반응 시 사운드

	UPROPERTY(EditAnywhere)
		bool bHitSingle = true;				// 하나의 대상에만 대미지를 줄 것인가
	UPROPERTY(EditAnywhere)
		bool bLifeSpan = true;				// 생명주기 설정
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bLifeSpan == true"))
		float lifeSpanValue;				// 생명주기 값 설정
	UPROPERTY(EditAnywhere)
		float damage;						// 대미지
	UPROPERTY(EditAnywhere)
		bool isSkill = false;				// 스킬공격인가?(스킬 or 기본공격)
	UPROPERTY(EditAnywhere)
		bool bIgnoreMyTeam = false;			// 내 팀은 무시하고 지나갈 것인가
	UPROPERTY(EditAnywhere)
		float falloffDistance = 1000.f;		// 사운드 범위

	UPROPERTY()
		TArray<class AActor*> hitActors;	// 대미지를 받은 ActorList
	bool isExplored = false;				// 이미 터졌는가?(중첩으로 터지는 것 방지)
public:
	// Overlap Event
	UFUNCTION()
		virtual void OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	void TurnOnCollision(bool bTurn);
	void SetDamage(float damageAmount) { damage = damageAmount; }	// 대미지 설정

	void Explored(FVector Location);
};

